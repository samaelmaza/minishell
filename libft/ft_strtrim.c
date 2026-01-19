/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:32:25 by sreffers          #+#    #+#             */
/*   Updated: 2025/09/29 15:29:09 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static size_t	trim_left(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && is_set(s1[i], set))
		i++;
	return (i);
}

static size_t	trim_right(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	if (i == 0)
		return (0);
	while (s1[i - 1] && is_set(s1[i - 1], set))
		i--;
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	size;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = trim_left(s1, set);
	end = trim_right(s1, set);
	if (end == 0 || start >= end)
		return (ft_strdup(""));
	size = end - start;
	str = ft_substr(s1, start, size);
	if (!str)
		return (NULL);
	return (str);
}

/*#include <stdio.h>
int main()
{
	char *str=ft_strtrim("xxxxhello worldxxxx", "x");
	printf("%s", str);
	free(str);
}*/
