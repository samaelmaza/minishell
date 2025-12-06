#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

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
};


#endif
