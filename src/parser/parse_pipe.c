/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:21:02 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 11:50:06 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast	*parse_primary(t_token **tokens, t_minishell *shell)
{
	t_ast	*node;
	t_ast	*subshell;

	if (check_token(*tokens, TOKEN_L_PARENT))
	{
		get_next_token(tokens);
		node = parse_logic(tokens, shell);
		if (!node)
			return (NULL);
		if (!check_token(*tokens, TOKEN_R_PARENT))
		{
			printf("Syntax error: missing closing parenthesis\n");
			shell->exit_code = 2;
			free_ast(node);
			return (NULL);
		}
		get_next_token(tokens);
		subshell = new_ast_node(NODE_SUBSHELL);
		if (!subshell)
		{
			free_ast(node);
			return (NULL);
		}
		subshell->left = node;
		return (subshell);
	}
	return (parse_cmd(tokens, shell));
}

t_ast	*parse_pipeline(t_token **tokens, t_minishell *shell)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_primary(tokens, shell);
	if (!left)
		return (NULL);
	if (check_token(*tokens, TOKEN_PIPE))
	{
		get_next_token(tokens);
		node = new_ast_node(NODE_PIPE);
		if (!node)
			//TODO clean ast
			return (NULL);
		node->left = left;
		node->right = parse_pipeline(tokens, shell);
		if (!node->right)
			return (NULL);
		return (node);
	}
	return (left);
}
t_ast	*parse_logic(t_token **tokens, t_minishell *shell)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_pipeline(tokens, shell);
	if (!left)
		return NULL;
	if (*tokens && ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR))
	{
		if ((*tokens)->type == TOKEN_AND)
			node = new_ast_node(NODE_AND);
		else
			node = new_ast_node(NODE_OR);
		if (!node) //TODO free_ast
			return (NULL);
		get_next_token(tokens);
		node->left = left;
		node->right = parse_logic(tokens, shell);
		if (!node->right)//TODO free_ast
			return (NULL);
		return (node);
	}
	return (left);
}
