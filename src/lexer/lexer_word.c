/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:25:00 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/18 19:25:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	get_word_len(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote != 0 && str[i] == quote)
			quote = 0;
		if (quote == 0 && (is_whitespace(str[i]) || is_separator(str[i])))
			break ;
		i++;
	}
	if (quote != 0)
		return (-1);
	return (i);
}

t_token	*handle_word(char *input, int *i)
{
	int		start;
	int		size;
	char	*word;
	t_token	*token;

	start = *i;
	size = get_word_len(input + start);
	if (size == -1)
	{
		printf("Error: Unclosed quotes\n");
		return (NULL);
	}
	word = ft_substr(input, start, size);
	if (!word)
		return (NULL);
	token = new_token(word, TOKEN_WORD);
	free(word);
	if (!token)
		return (NULL);
	*i += size;
	return (token);
}
