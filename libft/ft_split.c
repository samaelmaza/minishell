/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:27:21 by sreffers          #+#    #+#             */
/*   Updated: 2025/09/29 15:28:21 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(const char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], c))
			i++;
		if (s[i] && !is_sep(s[i], c))
			words++;
		while (s[i] && !is_sep(s[i], c))
			i++;
	}
	return (words);
}

static char	*fill_words(char const *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && !is_sep(s[i], c))
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && !is_sep(s[i], c))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	create_words(char const *s, char c, char **array_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_sep(s[i], c))
			i++;
		if (s[i] && !is_sep(s[i], c))
		{
			array_str[j] = fill_words(&s[i], c);
			j++;
		}
		while (s[i] && !is_sep(s[i], c))
			i++;
	}
	array_str[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**array_str;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array_str = malloc(sizeof(char *) * (words + 1));
	if (!array_str)
		return (NULL);
	create_words(s, c, array_str);
	return (array_str);
}

/*#include <stdio.h>
int	main()
{
	char c = ' ';
	char str[]="      split       this for   me  !       ";
	char **array = ft_split(str, c);
	int i = 0;
	while(array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	i= 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);

	//printf("%d", count_words(str, c));
}*/
