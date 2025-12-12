/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:42:16 by sreffers          #+#    #+#             */
/*   Updated: 2025/12/12 23:06:29 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// const char *get_token_type_name(t_token_type type)
// {
//     if (type == TOKEN_WORD) return "WORD";
//     if (type == TOKEN_PIPE) return "PIPE";
//     if (type == TOKEN_INPUT) return "<";
//     if (type == TOKEN_HEREDOC) return "<<";
//     if (type == TOKEN_TRUNC) return ">";
//     if (type == TOKEN_APPEND) return ">>";
//     if (type == TOKEN_AND) return "&&";
//     if (type == TOKEN_OR) return "||";
//     if (type == TOKEN_L_PARENT) return "(";
//     if (type == TOKEN_R_PARENT) return ")";
//     if (type == TOKEN_EOF) return "EOF";
//     return "UNKNOWN";
// }

// void    print_tokens(t_token *tokens)
// {
//     t_token *tmp;

//     tmp = tokens;
//     printf("\n--- DEBUT ANALYSE LEXER ---\n");
//     while (tmp)
//     {
//         printf("Type: %-10s | Value: [%s]\n",
//                get_token_type_name(tmp->type),
//                tmp->value ? tmp->value : "NULL");
//         tmp = tmp->next;
//     }
//     printf("--- FIN ANALYSE LEXER ---\n\n");
// }

void	init_minishell(t_minishell *shell, char **env)
{
	int		i;
	t_list	*new_node;
	char 	*content;

	i = 0;
	shell->env = NULL;
	shell->exit_code = 0;
	while(env[i])
	{
		content = ft_strdup(env[i]);
		if(!content)
			clean_exit(shell, EXIT_FAILURE);
		new_node = ft_lstnew(content);
		if(!new_node)
		{
			free(content);
			clean_exit(shell, EXIT_FAILURE);
		}
		ft_lstadd_back(&shell->env, new_node);
		i++;
	}
}

/* Fonction utilitaire pour imprimer N espaces */
void print_indent(int level)
{
    while (level > 0)
    {
        printf("    "); // 4 espaces par niveau
        level--;
    }
}

/* Fonction récursive d'affichage */
void print_ast(t_ast *node, int level)
{
    t_list  *tmp;
    t_redirection *redir;

    if (!node)
        return ;

    print_indent(level);

    // CAS 1 : C'est un PIPE
    if (node->type == NODE_PIPE)
    {
        printf("[ PIPE | ]\n");
        print_ast(node->left, level + 1);
        print_ast(node->right, level + 1);
    }
    // --- NOUVEAU : CAS 2 : C'est un ET / OU ---
    else if (node->type == NODE_AND || node->type == NODE_OR)
    {
        if (node->type == NODE_AND)
            printf("[ AND && ]\n");
        else
            printf("[ OR || ]\n");

        // On affiche les enfants récursivement
        print_ast(node->left, level + 1);
        print_ast(node->right, level + 1);
    }
    // ------------------------------------------
    // CAS 3 : C'est une COMMANDE
    else if (node->type == NODE_CMD)
    {
        printf("[ CMD ] args: ");
        tmp = node->args_list;
        while (tmp)
        {
            printf("'%s' ", (char *)tmp->content);
            tmp = tmp->next;
        }
        printf("\n");

        tmp = node->redirection;
        while (tmp)
        {
            redir = (t_redirection *)tmp->content;
            print_indent(level + 1);
            if (redir->type == TOKEN_TRUNC) printf("Redir: > %s\n", redir->path);
            else if (redir->type == TOKEN_APPEND) printf("Redir: >> %s\n", redir->path);
            else if (redir->type == TOKEN_INPUT) printf("Redir: < %s\n", redir->path);
            else if (redir->type == TOKEN_HEREDOC) printf("Redir: << %s\n", redir->path);
            tmp = tmp->next;
        }
    }
}
int main(int ac, char **av, char **env)
{
	t_minishell	shell;
	char		*input;
	t_ast		*ast;

	(void)av;
	if(ac != 1)
	{
		printf("only one argument mate\n");
		return (1);
	}
	init_minishell(&shell, env);
	while (1)
	{
		input = readline("minishell$> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if(input[0] != '\0')
		{
			add_history(input);

			if(lexer(&shell, input))
			{
				ast = parse_logic(&shell.token, &shell);
				if(ast)
				{
					print_ast(ast, 0);
				}
			}
		}
		free(input);
	}
	return (shell.exit_code);
}
