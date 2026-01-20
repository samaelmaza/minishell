/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:01:00 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/20 19:01:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	restore_wildcards(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == '\x01')
			*str = '*';
		str++;
	}
}

void	insert_wildcard_matches(t_list *current, char **matches)
{
	t_list	*saved_next;
	t_list	*new_node;
	int		i;

	saved_next = current->next;
	free(current->content);
	current->content = matches[0];
	i = 1;
	while (matches[i])
	{
		new_node = ft_lstnew(matches[i]);
		current->next = new_node;
		current = current->next;
		i++;
	}
	current->next = saved_next;
	free(matches);
}
