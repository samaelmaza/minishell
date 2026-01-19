/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 10:21:45 by sreffers          #+#    #+#             */
/*   Updated: 2025/09/28 16:31:15 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		n;
	long	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = str[i] - '0';
		result = (result * 10) + n;
		i++;
	}
	return (result * sign);
}

/*#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	printf("%d", ft_atoi("  \n  -+123456"));
	printf("%d", atoi("  \n  -+123456"));
}*/
