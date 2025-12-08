/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:42:16 by sreffers          #+#    #+#             */
/*   Updated: 2025/12/08 16:01:37 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int main(int ac, char **av, char **env)
{
	t_minishell	shell;
	char		*input;

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
		}
		free(input);
	}
	return (shell.exit_code);
}
