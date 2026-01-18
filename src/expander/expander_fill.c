/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:33:42 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/18 19:25:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(char *var, t_minishell *shell)
{
	int		size;
	t_list	*current;
	char	*content;

	current = shell->env;
	size = ft_strlen(var);
	while (current)
	{
		content = (char *)current->content;
		if (ft_strncmp(content, var, size) == 0 && content[size] == '=')
			return (content + size + 1);
		current = current->next;
	}
	return ("");
}

static void	copy_env_var(char *str, char *res, int *idx, t_minishell *shell)
{
	char	*var_val;
	char	*var_name;
	int		start;

	start = idx[0];
	while (ft_isalnum(str[idx[0]]) || str[idx[0]] == '_')
		(idx[0])++;
	var_name = ft_substr(str, start, idx[0] - start);
	var_val = get_env_value(var_name, shell);
	while (var_val && *var_val)
		res[(idx[1])++] = *var_val++;
	free(var_name);
}

static void	add_exit_code(char *res, int *idx, t_minishell *shell)
{
	char	*var_val;
	int		k;

	k = 0;
	var_val = ft_itoa(shell->exit_code);
	if (!var_val)
		return ;
	while (var_val[k])
		res[(idx[1])++] = var_val[k++];
	free(var_val);
}

static void	add_var_value(char *str, char *res, int *idx, t_minishell *shell)
{
	(idx[0])++;
	if (str[idx[0]] == '?')
	{
		(idx[0])++;
		add_exit_code(res, idx, shell);
	}
	else
		copy_env_var(str, res, idx, shell);
}

char	*expand_string(char *str, t_minishell *shell)
{
	char	*res;
	int		idx[3];

	idx[0] = 0;
	idx[1] = 0;
	idx[2] = 0;
	res = malloc(sizeof(char) * (get_expand_line(str, shell) + 1));
	if (!res)
		return (NULL);
	while (str[idx[0]])
	{
		if (is_quote_toggle(str[idx[0]], &idx[2]))
			(idx[0])++;
		else if (str[idx[0]] == '$' && idx[2] != 1 && is_var(str[idx[0] + 1]))
			add_var_value(str, res, idx, shell);
		else if (str[idx[0]] == '*' && idx[2] != 0)
		{
			res[(idx[1])++] = '\x01';
			(idx[0])++;
		}
		else
			res[(idx[1])++] = str[(idx[0])++];
	}
	res[idx[1]] = 0;
	return (res);
}
