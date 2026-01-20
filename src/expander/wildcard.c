/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:52:20 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/20 19:01:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		return (match_pattern(pattern + 1, str)
			|| match_pattern(pattern, str + 1));
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

static int	count_matches(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (-1);
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!(pattern[0] != '.' && entry->d_name[0] == '.'))
			if (match_pattern(pattern, entry->d_name))
				count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

static char	**fill_matches(char *pattern, int count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**result;
	int				i;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (free(result), NULL);
	i = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!(pattern[0] != '.' && entry->d_name[0] == '.'))
			if (match_pattern(pattern, entry->d_name))
				result[i++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	result[i] = NULL;
	closedir(dir);
	return (result);
}

char	**expand_wildcard(char *pattern)
{
	int	count;

	count = count_matches(pattern);
	if (count == -1)
		return (perror("opendir"), NULL);
	return (fill_matches(pattern, count));
}
