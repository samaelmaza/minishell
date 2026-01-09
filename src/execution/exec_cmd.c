/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:49:25 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 23:53:21 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**get_argv(t_list *args)
{
	int	len;
	int	i;
	char **new_args;

	len = ft_lstsize(args);
	i = 0;
	new_args = malloc(sizeof(char *) * (len + 1));
	if (!new_args)
		return (NULL);
	while (i < len)
	{
		new_args[i] = ft_strdup((char *)args->content);
		if(!new_args[i])
		{
			while(i > 0)
				free(new_args[--i]);
			free(new_args);
			return (NULL);
		}
		i++;
		args = args->next;
	}
	new_args[i] = 0;
	return new_args;
}
void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
int	exec_cmd(t_ast *node, t_minishell *shell)
{
	char	**av;
	char	**env;
	pid_t	pid;
	int		status;

	av = get_argv(node->args_list);
	env = env_list_to_tab(shell->env);
	if(!env || !av)
		return (1);
	pid = fork();
	if(pid == -1)
	{
		perror("Fork failed");
		free_tab(env);
		free_tab(av);
		return (1);
	}
	if(pid == 0)
	{
		if((execve(av[0], av, env)) == -1)
		{
			perror("minishell");
			free_tab(env);
			free_tab(av);
			shell->exit_code = 127;
			exit(127);
		}
	}
	free_tab(env);
	free_tab(av);
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
