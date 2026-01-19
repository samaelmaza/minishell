/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 14:44:31 by sreffers          #+#    #+#             */
/*   Updated: 2025/09/29 15:24:42 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_num(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	fill_str(char *str, long nb, int size)
{
	int	i;

	if (nb == 0)
	{
		str[0] = '0';
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	str[size] = '\0';
	i = size - 1;
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;
	long	nb;

	nb = n;
	size = size_num(nb);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	fill_str(str, nb, size);
	return (str);
}

/*#include <stdio.h>
int main()
{
	printf("%s\n", ft_itoa(+123459879));
}*/
