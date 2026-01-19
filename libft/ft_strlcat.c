/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:57:08 by sreffers          #+#    #+#             */
/*   Updated: 2025/09/28 16:26:26 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;

	if (!dst && size == 0)
		return (ft_strlen(src));
	i = 0;
	len_dest = 0;
	len_src = ft_strlen(src);
	while (dst[len_dest] && len_dest < size)
		len_dest++;
	if (size == len_dest)
		return (size + len_src);
	while (src[i] && (len_dest + i + 1) < size)
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	dst[len_dest + i] = '\0';
	return (len_dest + len_src);
}

/*#include <stdio.h>
int main()
{
	char dest[]="adios";
	char src[]="hola";
	printf("%ld", ft_strlcat(dest, src, 3));
	printf("%s", dest);
}*/
