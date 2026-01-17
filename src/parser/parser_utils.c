/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 21:39:09 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 23:34:21 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_token(t_token *token, t_token_type type)
{
	if (token && token->type == type)
		return (1);
	return (0);
}

t_token	*get_next_token(t_token **token)
{
	t_token	*current;
	if (!*token)
		return (NULL);
	current = *token;
	*token = (*token)->next;
	return (current);
}
t_ast	*new_ast_node(t_node_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->args_list = NULL;
	node->redirection = NULL;
	return (node);
}

int	append_arg(t_ast *node, char *value)
{
	char	*cpy;
	t_list	*new_arg;

	if (!node || !value)
		return (0);
	cpy = ft_strdup(value);
	if (!cpy)
		return (0);
	new_arg = ft_lstnew(cpy);
	if (!new_arg)
	{
		free(cpy);
		return (0);
	}
	ft_lstadd_back(&node->args_list, new_arg);
	return (1);
}
