/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:42:16 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/15 22:47:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_minishell(t_minishell *shell, char **env)
{
	int		i;
	t_list	*new_node;
	char	*content;

	i = 0;
	shell->env = NULL;
	shell->exit_code = 0;
	shell->is_child = 0;
	while (env[i])
	{
		content = ft_strdup(env[i]);
		if (!content)
			clean_exit(shell, EXIT_FAILURE);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			free(content);
			clean_exit(shell, EXIT_FAILURE);
		}
		ft_lstadd_back(&shell->env, new_node);
		i++;
	}
}

static void	process_input(t_minishell *shell, char *input)
{
	t_token	*parse_token;

	add_history(input);
	if (lexer(shell, input))
	{
		parse_token = shell->token;
		shell->ast = parse_logic(&parse_token, shell);
		if (shell->ast)
		{
			expand_ast(shell->ast, shell);
			execute_ast(shell->ast, shell);
			free_ast(shell->ast);
			shell->ast = NULL;
		}
	}
	free_token(&shell->token);
}

static void	shell_loop(t_minishell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] != '\0')
			process_input(shell, input);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	shell;

	init_signals();
	(void)av;
	if (ac != 1)
	{
		printf("only one argument mate\n");
		return (1);
	}
	init_minishell(&shell, env);
	shell.ast = NULL;
	shell_loop(&shell);
	if (shell.env)
		ft_lstclear(&shell.env, del_content);
	rl_clear_history();
	return (shell.exit_code);
}
