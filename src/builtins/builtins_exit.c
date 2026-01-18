/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 00:29:03 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/17 00:56:09 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_overflow(char *str)
{
	int		i;
	int		sign;
	long	result;
	int		digit;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		digit = str[i] - '0';
		if (sign == 1 && result > (LONG_MAX - digit) / 10)
			return (1);
		if (sign == -1 && (0 - result) < (LONG_MIN + digit) / 10)
			return (1);
		result = result * 10 + digit;
		i++;
	}
	return (0);
}

static void	exit_numeric_error(char *arg, t_minishell *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	clean_exit(shell, 2);
}

int	ft_exit(char **args, t_minishell *shell)
{
	long	status;

	ft_putendl_fd("exit", 2);
	if (!args[1])
		clean_exit(shell, shell->exit_code);
	if (!is_numeric(args[1]) || is_overflow(args[1]))
		exit_numeric_error(args[1], shell);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	status = ft_atol(args[1]);
	clean_exit(shell, (unsigned char)status);
	return (0);
}
