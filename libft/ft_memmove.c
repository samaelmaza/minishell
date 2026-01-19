/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:26:47 by sreffers          #+#    #+#             */
/*   Updated: 2025/10/01 13:18:40 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (dest < source)
	{
		return (ft_memcpy(dst, src, len));
	}
	else
	{
		i = len;
		while (i > 0)
		{
			dest[i - 1] = source[i - 1];
			i--;
		}
	}
	return (dst);
}

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char str1[20] = "Hello World";
    char str2[20] = "Hello World";
    char *buf1 = malloc(12);
    char *buf2 = malloc(12);

    printf("%s\n", str1);
    ft_memmove(str1 + 6, str1, 5);
    printf("%s\n\n", str1);

	char str3[11] = "1234567890";
    printf("%s\n", str3);
    ft_memmove(str3, str3 + 2, 8);
	//memmove(str3, str3 + 2, 8);
    printf("%s\n\n", str3);

    free(buf1);
    free(buf2);

    return 0;
}*/
