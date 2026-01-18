/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:40:01 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/18 19:25:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			is_whitespace(char c);
int			is_separator(char c);
t_token		*handle_word(char *input, int *i);

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
