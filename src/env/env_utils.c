/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:55:00 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 23:04:02 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**env_list_to_tab(t_list *env)
{
	int	len;
	int	i;
	char **new_env;

	len = ft_lstsize(env);
	i = 0;
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	while (i < len)
	{
		new_env[i] = ft_strdup((char *)env->content);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	new_env[i] = 0;
	return new_env;
}
