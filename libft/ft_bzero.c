/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:06:00 by sreffers          #+#    #+#             */
/*   Updated: 2025/09/28 15:54:01 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < len)
	{
		str[i] = 0;
		i++;
	}
}

/*#include <stdio.h>
#include <string.h>

int main()
{
    char str1[50] = "Hello, World!";
    char str2[50] = "Hello, World!";
    ft_bzero(str1, 5);
    bzero(str2, 5);
    printf("ft_bzero: %s\n", str1);
    printf("bzero: %s\n", str2);
    return (0);
}*/

/*unsigned char *p = (unsigned char *)s; best way to do it
while (n--)
    *p++ = 0;*/
