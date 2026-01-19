/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:04:16 by sreffers          #+#    #+#             */
/*   Updated: 2025/09/28 15:53:57 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

/*#include <stdio.h>
#include <string.h>

int main()
{
    char str1[50] = "Hello, World!";
    char str2[50] = "Hello, World!";
    ft_memset(str1, 'X', 5);
    memset(str2, 'X', 5);
    printf("ft_memset: %s\n", str1);
    printf("memset: %s\n", str2);
    return (0);
}*/
