/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:33:42 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 18:16:17 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	copy_env_var(char *str, char *res, int *i, int *j, t_minishell *shell)
{
	char	*var_val;
	char	*var_name;
	int		start;
	int		k;

	start = *i;
	while(ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	var_val = get_env_value(var_name, shell);
	if(var_val)
	{
		while(var_val[k])
			res[(*j)++] = var_val[k++];
	}
	free(var_name);
}

void	add_var_value(char *str, char *res, int *i, int *j, t_minishell *shell)
{
	char	*var_val;
	int		k;

	k = 0;
	(*i)++;
	if(str[*i + 1] == '?')
	{
		(*i)++;
		var_val = ft_itoa(shell->exit_code);
		if(!var_val)
			return ;
		while(var_val[k])
			res[(*j)++] = var_val[k++];
		free(var_val);
	}
	else
		copy_env_var(str, res, &i, &j, shell);
}

char	*expand_string(char *str, t_minishell *shell)
{
	char	*res;
	int		len;
	int		i;
	int		j;
	int		quote;

	res = malloc(sizeof(char) * (get_expand_line(str, shell) + 1));
	if(!res)
		return (NULL);
	while(str[i])
	{
		if(is_quote_toggle(str[i], &quote))
			i++;
		else if(str[i] == '$' && quote != 1 && is_var(str[i + 1]))
			add_var_value(str, res, &i, &j, shell);
		else
			res[j++] = str[i++];
	}
	res[j] = 0;
	return (res);
}
