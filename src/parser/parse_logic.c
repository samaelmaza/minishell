/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:00:00 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/20 19:00:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_ast	*create_logic_node(t_token **tokens)
{
	t_ast	*node;

	if ((*tokens)->type == TOKEN_AND)
		node = new_ast_node(NODE_AND);
	else
		node = new_ast_node(NODE_OR);
	return (node);
}

t_ast	*parse_logic(t_token **tokens, t_minishell *shell)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_pipeline(tokens, shell);
	if (!left)
		return (NULL);
	if (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		node = create_logic_node(tokens);
		if (!node)
			return (free_ast(left), NULL);
		get_next_token(tokens);
		node->left = left;
		node->right = parse_logic(tokens, shell);
		if (!node->right)
			return (free_ast(node), NULL);
		return (node);
	}
	return (left);
}
