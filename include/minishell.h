/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:42:21 by sreffers          #+#    #+#             */
/*   Updated: 2025/12/08 21:00:14 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_token t_token;

typedef struct s_minishell
{
	t_list  *env;
	int		exit_code;
	t_token	*token;
}	t_minishell;

typedef enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INPUT,
	TOKEN_HEREDOC,
	TOKEN_TRUNC,
	TOKEN_APPEND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_L_PARENT,
	TOKEN_R_PARENT,
	TOKEN_EOF
}	t_token_type;
typedef struct s_redirection
{
	t_token_type	type;   // TOKEN_INPUT, TRUNC, APPEND ou HEREDOC
	char			*path;  // Le nom du fichier (ou le délimiteur heredoc)
	// char         **expanded_args; // (Pour plus tard: si le nom du fichier est une var $FILE)
}	t_redirection;

typedef enum	e_node_type
{
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_CMD
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			**args;
	t_list			*redirection;
}	t_ast;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

void	clean_exit(t_minishell *shell, int exit_code);
void	token_add_back(t_token **lst, t_token *new);
t_token	*new_token(char	*value, t_token_type type);
t_token	*handle_separator(char *input, int *i);
int		lexer(t_minishell *shell, char *input);

#endif
