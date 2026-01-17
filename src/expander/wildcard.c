/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:52:20 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/17 17:38:57 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Restore \x01 back to * after wildcard expansion
** This is needed because quoted * were converted to \x01 to protect them
*/
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

void	insert_wildcard_matches(t_list	*current, char **matches)
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

int	match_pattern(char *pattern, char *str)
{
	if (*pattern == 0 && *str == 0)
		return (1);
	if (*pattern == 0)
		return (0);
	if (*str == 0)
	{
		if (*pattern == '*')
			return (match_pattern(pattern + 1, str));
		return (0);
	}
	if (*pattern == '*')
		return (match_pattern(pattern + 1, str) || match_pattern(pattern, str + 1));
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

char **expand_wildcard(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;
	int				i;
	char			**result;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return (NULL);
	}
	count = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (pattern[0] != '.' && entry->d_name[0] == '.')
			continue;
		if (match_pattern(pattern, entry->d_name))
			count++;
	}
	closedir(dir);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (0);
	dir = opendir(".");
	if (!dir)
	{
		free_tab(result);
		perror("opendir");
		return (NULL);
	}
	i = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (pattern[0] != '.' && entry->d_name[0] == '.')
			continue;
		if (match_pattern(pattern, entry->d_name))
			result[i++] = ft_strdup(entry->d_name);
	}
	result[i] = 0;
	closedir(dir);
	return (result);
}
