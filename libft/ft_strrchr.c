/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 09:46:36 by sreffers          #+#    #+#             */
/*   Updated: 2025/10/01 14:28:17 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = (int)ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char) c)
		{
			return ((char *)(s + i));
		}
		i--;
	}
	return (NULL);
}

/*#include <stdio.h>
int main()
{
	char *str = "Hello World";
	printf("%s\n",ft_strrchr(str, '\0') - 1);
}*/
