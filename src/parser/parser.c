/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:12:08 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 11:50:26 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_redir(t_ast *node, t_token **tokens, t_minishell *shell)
{
	t_token 		*operator;
	t_token			*file;
	t_redirection	*redir;
	t_list			*new_node;

	operator = *tokens;
	file = (*tokens)->next;
	if(!file || file->type != TOKEN_WORD)
	{
		printf("Syntax error near unexpected token");
		shell->exit_code = 2;
		return (0);
	}

	redir = malloc(sizeof(t_redirection));
	if(!redir)
		return (0);
	redir->type = operator->type;
	redir->path = ft_strdup(file->value);
	if(!redir->path)
	{
		free(redir);
		return (0);
	}
	new_node = ft_lstnew(redir);
	if (!new_node)
	{
		free(redir->path);
		free(redir);
		return (0);
	}
	ft_lstadd_back(&node->redirection, new_node);
	*tokens = file->next;
	return (1);

}

t_ast	*parse_cmd(t_token **tokens, t_minishell *shell)
{
	t_ast	*node;

	if(check_token(*tokens, TOKEN_PIPE) || check_token(*tokens, TOKEN_AND)
		|| check_token(*tokens, TOKEN_OR) || check_token(*tokens, TOKEN_R_PARENT))
	{
		printf("Syntax error near unexpected token");
		shell->exit_code = 2;
		return (NULL);
	}
	node = new_ast_node(NODE_CMD);
	if(!node)
		return (NULL);
	while(*tokens)
	{
		t_token_type type = (*tokens)->type;

		if (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_R_PARENT || type == TOKEN_EOF)
			break ;
		else if (type == TOKEN_HEREDOC || type == TOKEN_INPUT || type == TOKEN_APPEND || type == TOKEN_TRUNC)
		{
			if(!parse_redir(node, tokens, shell))
			{
				free(node);
				return NULL;
			}
		}
		else if (type == TOKEN_WORD)
		{
			if(!append_arg(node, (*tokens)->value))
			{
				free(node);
				return (NULL);
			}
			get_next_token(tokens);
		}
		else
		{
			printf("Syntax error near unexpected token\n");
			free(node);
			shell->exit_code = 2;
			return (NULL);
		}
	}
	return (node);
}
