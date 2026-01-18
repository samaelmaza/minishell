/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:42:21 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/18 19:10:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>

typedef struct s_token	t_token;
typedef struct s_ast	t_ast;

typedef struct s_minishell
{
	t_list	*env;
	int		exit_code;
	t_token	*token;
	t_ast	*ast;
	int		is_child;
}	t_minishell;

typedef enum e_token_type
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
	t_token_type	type;
	char			*path;
}	t_redirection;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_CMD,
	NODE_SUBSHELL
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_list			*redirection;
	t_list			*args_list;
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
int		check_token(t_token *token, t_token_type type);
t_token	*get_next_token(t_token **token);
t_ast	*new_ast_node(t_node_type type);
int		append_arg(t_ast *node, char *value);
t_ast	*parse_cmd(t_token **tokens, t_minishell *shell);
t_ast	*parse_pipeline(t_token **tokens, t_minishell *shell);
t_ast	*parse_logic(t_token **tokens, t_minishell *shell);
int		get_expand_line(char *str, t_minishell *shell);
char	*get_env_value(char *var, t_minishell *shell);
int		is_quote_toggle(char c, int *quote);
int		is_var(char c);
char	*expand_string(char *str, t_minishell *shell);
void	expand_ast(t_ast *node, t_minishell *shell);
int		execute_ast(t_ast *node, t_minishell *shell);
int		exec_pipe(t_ast *node, t_minishell *shell);
int		exec_cmd(t_ast *node, t_minishell *shell);
char	**env_list_to_tab(t_list *env);
void	free_ast(t_ast *node);
void	del_content(void *content);
void	free_token(t_token **token);
void	free_child(t_minishell *shell);
int		handle_redirections(t_list *redirection);
int		collect_heredocs_ast(t_ast *node);
void	init_signals(void);
void	set_childs_signals(void);
void	ignore_signals(void);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_minishell *shell);
int		is_builtin(char *cmd);
char	**get_argv(t_list *args);
int		get_exit_status(int status);
int		exec_builtin(t_ast *node, t_minishell *shell);
void	free_tab(char **tab);
void	update_env(t_minishell *shell, char *str);
int		is_valid_env_key(char *key);
int		ft_export(char **args, t_minishell *shell);
int		ft_unset(char **args, t_minishell *shell);
int		ft_cd(char **args, t_minishell *shell);
int		ft_exit(char **args, t_minishell *shell);
int		has_wildcard(char *str);
int		match_pattern(char *pattern, char *str);
char	**expand_wildcard(char *pattern);
void	insert_wildcard_matches(t_list *current, char **matches);
void	restore_wildcards(char *str);

#endif
