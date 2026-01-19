/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:07:21 by sreffers          #+#    #+#             */
/*   Updated: 2025/09/28 15:53:57 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	size;
	unsigned int	i;
	char			*str;

	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*char my_func(unsigned int i, char c)
{
    if (i % 2 == 0)
        return (c - 32);
    return c;
}

#include <stdio.h>
int main()
{
    char *res = ft_strmapi("abcdef", my_func);
    printf("%s\n", res);
    free(res);
}*/
