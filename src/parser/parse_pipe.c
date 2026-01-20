/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:21:02 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/20 19:00:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast	*make_subshell_node(t_ast *node, t_minishell *shell)
{
	t_ast	*subshell;

	if (!check_token(NULL, TOKEN_R_PARENT) && !node)
		return (NULL);
	subshell = new_ast_node(NODE_SUBSHELL);
	if (!subshell)
	{
		free_ast(node);
		return (NULL);
	}
	subshell->left = node;
	(void)shell;
	return (subshell);
}

static t_ast	*parse_subshell(t_token **tokens, t_minishell *shell)
{
	t_ast	*node;

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
	return (make_subshell_node(node, shell));
}

static t_ast	*parse_primary(t_token **tokens, t_minishell *shell)
{
	if (check_token(*tokens, TOKEN_L_PARENT))
		return (parse_subshell(tokens, shell));
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
			return (free_ast(left), NULL);
		node->left = left;
		node->right = parse_pipeline(tokens, shell);
		if (!node->right)
			return (free_ast(node), NULL);
		return (node);
	}
	return (left);
}
