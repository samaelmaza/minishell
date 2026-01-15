/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:49:25 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/15 23:30:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/stat.h>

char	**get_argv(t_list *args)
{
	int		len;
	int		i;
	char	**new_args;

	len = ft_lstsize(args);
	i = 0;
	new_args = malloc(sizeof(char *) * (len + 1));
	if (!new_args)
		return (NULL);
	while (i < len)
	{
		new_args[i] = ft_strdup((char *)args->content);
		if (!new_args[i])
		{
			while (i > 0)
				free(new_args[--i]);
			free(new_args);
			return (NULL);
		}
		i++;
		args = args->next;
	}
	new_args[i] = 0;
	return (new_args);
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
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
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

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	path_var = get_env_value("PATH", shell);
	if (!path_var || *path_var == '\0')
		return (ft_strdup(cmd));
	paths = ft_split(path_var, ':');
	if (!paths)
		return (ft_strdup(cmd));
	final_path = search_in_paths(paths, cmd);
	free_tab(paths);
	if (final_path)
		return (final_path);
	return (NULL);
}

static int	check_cmd_errors(char *path, char *cmd)
{
	struct stat	st;

	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	if (stat(path, &st) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	return (0);
}

static void	child_cleanup(char *path, char **av, char **env, t_minishell *sh)
{
	if (path)
		free(path);
	if (av)
		free_tab(av);
	if (env)
		free_tab(env);
	free_child(sh);
}

static void	child_routine(t_ast *node, t_minishell *sh, char *path, char **av)
{
	char	**env;
	int		err;

	env = env_list_to_tab(sh->env);
	set_childs_signals();
	if (node->redirection && handle_redirections(node->redirection) != 0)
	{
		child_cleanup(path, av, env, sh);
		exit(1);
	}
	err = check_cmd_errors(path, av[0]);
	if (err != 0)
	{
		child_cleanup(path, av, env, sh);
		exit(err);
	}
	execve(path, av, env);
	perror("minishell");
	child_cleanup(path, av, env, sh);
	exit(1);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	exec_cmd(t_ast *node, t_minishell *shell)
{
	char	**av;
	pid_t	pid;
	int		status;
	char	*path;

	av = get_argv(node->args_list);
	if (!av || !av[0])
	{
		if (av)
			free_tab(av);
		return (0);
	}
	path = get_cmd_path(av[0], shell);
	if (shell->is_child == 1)
		child_routine(node, shell, path, av);
	pid = fork();
	if (pid == 0)
		child_routine(node, shell, path, av);
	if (path)
		free(path);
	free_tab(av);
	if (pid == -1)
		return (perror("fork"), 1);
	ignore_signals();
	waitpid(pid, &status, 0);
	init_signals();
	return (get_exit_status(status));
}
