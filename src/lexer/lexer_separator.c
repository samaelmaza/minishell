/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_separator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:51:45 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 11:49:13 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*handle_redirect(char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			*i += 2;
			return (new_token("<<", TOKEN_HEREDOC));
		}
		(*i)++;
		return (new_token("<", TOKEN_INPUT));
	}
	else
	{
		if (input[*i + 1] == '>')
		{
			*i += 2;
			return (new_token(">>", TOKEN_APPEND));
		}
		(*i)++;
		return (new_token(">", TOKEN_TRUNC));
	}
}

static t_token	*handle_logic(char *input, int *i)
{
	if (input[*i] == '&')
	{
		*i += 2;
		return (new_token("&&", TOKEN_AND));
	}
	if (input[*i] == '|' && input[*i + 1] == '|')
	{
		*i += 2;
		return (new_token("||", TOKEN_OR));
	}
	(*i)++;
	return (new_token("|", TOKEN_PIPE));
}

static t_token	*handle_paren(char *input, int *i)
{
	if (input[*i] == '(')
	{
		(*i)++;
		return (new_token("(", TOKEN_L_PARENT));
	}
	(*i)++;
	return (new_token(")", TOKEN_R_PARENT));
}

t_token	*handle_separator(char *input, int *i)
{
	char	c;

	c = input[*i];
	if (c == '<' || c == '>')
		return (handle_redirect(input, i));
	if (c == '|' || c == '&')
		return (handle_logic(input, i));
	if (c == '(' || c == ')')
		return (handle_paren(input, i));
	return (NULL);
}
