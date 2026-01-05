/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:26:11 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/05 20:08:08 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(char *var, t_minishell *shell)
{
	int	size;
	t_list	*current;
	char	*content;

	current = shell->env;
	size = ft_strlen(var);
	while(current)
	{
		content = (char *)current->content;
		if (ft_strncmp(content, var, size) == 0)
		{
			if (content[size] == '=')
				return (content + size + 1);
		}
		current = current->next;
	}
	return ("");
}

int	len_exit_code(int exit_code)
{
	int len = 0;
	while (exit_code > 0)
	{
		exit_code = exit_code/10;
		len++;
	}
	return (len);
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
	int quote = 0; // 0 = default 1 =  ' 2 = ""

	i = 0;
	len = 0;
	while(str[i])
	{
		if (str[i] == '\'')
		{
			if(quote == 2)
				len++;
			if(quote == 0)
				quote = 1;
			else if(quote == 1)
				quote = 0;
			i++;
		}
		else if (str[i] == '"')
		{
			if (quote == 1)
				len++;
			if (quote == 0)
				quote = 2;
			else if (quote == 2)
				quote = 0;
		}
		else if (str[i] == "$" && quote != 1)
			len += get_var_len(str, &i, shell);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
