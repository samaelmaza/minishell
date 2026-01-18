/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:09:28 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/16 21:37:12 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_env_node(t_minishell *shell, char *key)
{
	t_list	*current;
	t_list	*prev;
	int		len;
	char	*content;

	if (!shell->env || !key)
		return ;
	current = shell->env;
	prev = NULL;
	len = ft_strlen(key);
	while (current)
	{
		content = (char *)current->content;
		if (ft_strncmp(content, key, len) == 0
			&& (content[len] == '=' || content[len] == '\0'))
		{
			if (prev == NULL)
				shell->env = current->next;
			else
				prev->next = current->next;
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(char **args, t_minishell *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		delete_env_node(shell, args[i]);
		i++;
	}
	return (0);
}
