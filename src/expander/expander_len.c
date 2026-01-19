/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:33:29 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/19 16:07:07 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_quote_toggle(char c, int *quote)
{
	if (c == '\'' && *quote != 2)
	{
		if (*quote == 0)
			*quote = 1;
		else
			*quote = 0;
		return (1);
	}
	if (c == '"' && *quote != 1)
	{
		if (*quote == 0)
			*quote = 2;
		else
			*quote = 0;
		return (1);
	}
	return (0);
}

int	len_exit_code(int exit_code)
{
	int	len;

	len = 0;
	if (exit_code == 0)
		return (1);
	while (exit_code > 0)
	{
		exit_code = exit_code / 10;
		len++;
	}
	return (len);
}

int	is_var(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

int	get_var_len(char *str, int *i, t_minishell *shell)
{
	char	*var_name;
	char	*var_value;
	int		len;
	int		start;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (len_exit_code(shell->exit_code));
	}
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	var_value = get_env_value(var_name, shell);
	len = ft_strlen(var_value);
	free(var_name);
	return (len);
}

int	get_expand_line(char *str, t_minishell *shell)
{
	int	i;
	int	len;
	int	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote_toggle(str[i], &quote))
			i++;
		else if (str[i] == '$' && quote != 1 && is_var(str[i + 1]))
			len += get_var_len(str, &i, shell);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
