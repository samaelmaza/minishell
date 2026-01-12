/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:49:25 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/13 00:06:04 by sreffers         ###   ########.fr       */
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
static char	*search_in_paths(char **paths, char *cmd)
{
	char	*temp;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if(!temp)
			return (cmd);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if(access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
char	*get_cmd_path(char *cmd, t_minishell *shell)
{
	char	*path_var;
	char	**paths;
	char	*final_path;

	if((cmd && ft_strchr(cmd, '/') != 0) || cmd[0] == '.')
		return (ft_strdup(cmd));
	path_var = get_env_value("PATH", shell);
	if (!path_var)
		return (ft_strdup(cmd));
	paths = ft_split(path_var, ':');
	final_path = search_in_paths(paths, cmd);
	free_tab(paths);
	if(final_path)
		return (final_path);
	return (ft_strdup(cmd));
	if(!paths)
		return (ft_strdup(cmd));
}

void	child_routine(t_ast *node, t_minishell *shell, char *path, char **av, char **env)
{
	if(node->redirection)
		{
			if(handle_redirections(node->redirection) != 0)
			{
				free(path);
				free_tab(env);
				free_tab(av);
				free_child(shell);
				exit(1);
			}
		}
		if((execve(path, av, env)) == -1)
		{
			perror("minishell");
			free(path);
			free_tab(env);
			free_tab(av);
			shell->exit_code = 127;
			free_child(shell);
			exit(127);
		}
}

int	exec_cmd(t_ast *node, t_minishell *shell)
{
	char	**av;
	char	**env;
	pid_t	pid;
	int		status;
	char	*path;

	av = get_argv(node->args_list);
	env = env_list_to_tab(shell->env);
	if(!env || !av)
		return (1);
	path = get_cmd_path(av[0], shell);
	if (shell->is_child == 1)
		child_routine(node, shell, path, av, env);
	pid = fork();
	if(pid == 0)
		child_routine(node, shell, path, av, env);
	free(path);
	free_tab(env);
	free_tab(av);
	if(pid == -1)
		return (perror("fork"), 1);
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
