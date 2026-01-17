/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:40:01 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/10 22:45:18 by sreffers         ###   ########.fr       */
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
	int 	size;
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

static t_token	*get_next_lex_token(char *input, int *i)
{
	if (is_separator(input[*i]))
		return (handle_separator(input, i));
	return (handle_word(input, i));
}

int	lexer(t_minishell *shell, char *input)
{
	int		i;
	t_token	*new;

	i = 0;
	shell->token = NULL;
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		new = get_next_lex_token(input, &i);
		if (!new)
		{
			free_token(&shell->token);
			shell->exit_code = 2;
			return (0);
		}
		token_add_back(&shell->token, new);
	}
	token_add_back(&shell->token, new_token(NULL, TOKEN_EOF));
	return (1);
}
