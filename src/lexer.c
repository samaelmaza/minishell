/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:40:01 by sreffers          #+#    #+#             */
/*   Updated: 2025/12/08 16:57:02 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_separator(char c)
{
	char	*sep;
	int		i;

	i = 0;
	sep = "|<>&()";
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	lexer(t_minishell *shell, char *input)
{
	int		i;
	t_token	*new;

	i = 0;
	while (input[i])
	{
		if (is_whitespace(input[i]))
		{
			i++;
			continue ;
		}
		if (is_separator(input[i]))
			new = handle_separator(input, &i);
		else
			new = handle_word(input, &i);
		if(!new)
			return (0);
		token_add_back()
	}
}
