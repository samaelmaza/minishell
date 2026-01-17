/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:12:08 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/15 22:47:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	create_redir_node(t_ast *node, t_token *op, t_token *file)
{
	t_redirection	*redir;
	t_list			*new_node;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (0);
	redir->type = op->type;
	redir->path = ft_strdup(file->value);
	if (!redir->path)
		return (free(redir), 0);
	new_node = ft_lstnew(redir);
	if (!new_node)
	{
		free(redir->path);
		free(redir);
		return (0);
	}
	ft_lstadd_back(&node->redirection, new_node);
	return (1);
}

int	parse_redir(t_ast *node, t_token **tokens, t_minishell *shell)
{
	t_token	*operator;
	t_token	*file;

	operator = *tokens;
	file = (*tokens)->next;
	if (!file || file->type != TOKEN_WORD)
	{
		printf("Syntax error near unexpected token\n");
		shell->exit_code = 2;
		return (0);
	}
	if (!create_redir_node(node, operator, file))
		return (0);
	*tokens = file->next;
	return (1);
}

static int	is_stop_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND
		|| type == TOKEN_OR || type == TOKEN_R_PARENT || type == TOKEN_EOF);
}

static int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_HEREDOC || type == TOKEN_INPUT
		|| type == TOKEN_APPEND || type == TOKEN_TRUNC);
}

static int	handle_cmd_token(t_ast *node, t_token **tok, t_minishell *shell)
{
	t_token_type	type;

	type = (*tok)->type;
	if (is_redir_token(type))
	{
		if (!parse_redir(node, tok, shell))
			return (-1);
	}
	else if (type == TOKEN_WORD)
	{
		if (!append_arg(node, (*tok)->value))
			return (-1);
		get_next_token(tok);
	}
	else
	{
		printf("Syntax error near unexpected token\n");
		shell->exit_code = 2;
		return (-1);
	}
	return (0);
}

t_ast	*parse_cmd(t_token **tokens, t_minishell *shell)
{
	t_ast	*node;

	if (check_token(*tokens, TOKEN_PIPE) || check_token(*tokens, TOKEN_AND)
		|| check_token(*tokens, TOKEN_OR) || check_token(*tokens, TOKEN_R_PARENT))
	{
		printf("Syntax error near unexpected token\n");
		shell->exit_code = 2;
		return (NULL);
	}
	node = new_ast_node(NODE_CMD);
	if (!node)
		return (NULL);
	while (*tokens && !is_stop_token((*tokens)->type))
	{
		if (handle_cmd_token(node, tokens, shell) == -1)
		{
			free_ast(node);
			return (NULL);
		}
	}
	return (node);
}
