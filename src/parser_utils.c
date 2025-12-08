/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:39:09 by sreffers          #+#    #+#             */
/*   Updated: 2025/12/08 21:47:50 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_token(t_token *token, t_token_type type)
{
	if(token && token->type == type)
		return (1);
	return (0);
}

t_token	*get_next_token(t_token **token)
{
	t_token	*current;
	if(!*token)
		return (NULL);
	current = *token;
	*token = (*token)->next;
	return (current);
}
t_ast   *new_ast_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	node->redirection = NULL;
	return (node);
}
