/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:06:53 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/10 22:42:50 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char	*value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token *last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}
