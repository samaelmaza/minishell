/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:08:38 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/16 13:18:32 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_env_key(char *key)
{
	int	i;

	if(!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while(key[i] && key[i] != '=')
	{
		if(!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	update_env(t_minishell *shell, char *str)
{
	char	*key;
	char	*equal_pos;
	t_list	*node;
	int		key_len;

	equal_pos = ft_strchr(str, '=');
	if(equal_pos)
		key_len = equal_pos - str;
	else
		key_len = ft_strlen(str);
	key = ft_substr(str, 0, key_len);
	if(!key)
		return ;
	node = find_env_node(shell->env, key);
}
