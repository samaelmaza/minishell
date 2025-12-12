/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:26:11 by sreffers          #+#    #+#             */
/*   Updated: 2025/12/13 00:36:49 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(char *var, t_minishell *shell)
{
	int	size;
	t_list	*current;
	char	*content;

	current = shell->env;
	size = ft_strlen(var);
	while(current)
	{
		content = (char *)current->content;
		if(ft_strncmp(content, var, size) == 0)
		{
			if(content[size] == '=')
				return (content + size + 1);
		}
		current = current->next;
	}
	return ("");
}

// int	get_expand_line(char *str, t_minishell *shell)
// {
// 	int	i;
// 	int	len;
// 	int quote = 0; // 1 ' 2 ""

// 	i = 0;
// 	len = 0;
// 	while(str[i])
// 	{
// 		if(str[i] == )
// 	}
// }
