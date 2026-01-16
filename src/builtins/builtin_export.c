/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:37:43 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/16 13:14:52 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_sort_tab(char **tab)
{
	int		len;
	int		i;
	int 	j;
	char	*temp;

	len = 0;
	while(tab[len])
		len++;
	while(i < len)
	{
		j = i + 1;
		while(j < len)
		{
			if(ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void print_sorted_env(t_minishell *shell)
{
	char	**tab;
	int		len;
	int		i;

	tab = env_list_to_tab(shell->env);
	ft_sort_tab(tab);
	i = 0;
	while(tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
	free_tab(tab);
}

int	ft_export(char **args, t_minishell *shell)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	if(!args[1])
	{
		print_sorted_env(shell);
		return (0);
	}
	i = 1;
	while(args[i])
	{
		if(is_valid_env_key(args[i]))
			update_env(shell, args[i]);

	}
}
