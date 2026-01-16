/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:08:38 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/16 20:42:52 by sreffers         ###   ########.fr       */
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
t_list	*find_env_node(t_list *env, char *key)
{
	t_list	*tmp;
	int		len;
	char	*content;

	tmp = env;
	len = ft_strlen(key);
	while(tmp)
	{
		content = (char *)tmp->content;
		if(ft_strncmp(content, key, len) == 0)
		{
			if(content[len] == '=' || content[len] == '\0')
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
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
	free(key);
	if(node)
	{
		if(equal_pos || ft_strchr((char *)node->content, '=') == NULL)
		{
			free(node->content);
			node->content = ft_strdup(str);
		}
	}
	else
		ft_lstadd_back(&shell->env, ft_lstnew(ft_strdup(str)));
}
