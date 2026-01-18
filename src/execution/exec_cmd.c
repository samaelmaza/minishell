/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:49:25 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/18 19:30:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/stat.h>

char	*get_cmd_path(char *cmd, t_minishell *shell);

static int	print_cmd_error(char *cmd, char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	return (code);
}

static int	check_cmd_errors(char *path, char *cmd)
{
	struct stat	st;

	if (!path)
		return (print_cmd_error(cmd, ": command not found\n", 127));
	if (stat(path, &st) == -1)
		return (print_cmd_error(cmd, ": No such file or directory\n", 127));
	if (S_ISDIR(st.st_mode))
		return (print_cmd_error(cmd, ": Is a directory\n", 126));
	if (access(path, X_OK) == -1)
		return (print_cmd_error(cmd, ": Permission denied\n", 126));
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

int	exec_cmd(t_ast *node, t_minishell *shell)
{
	char	**av;
	pid_t	pid;
	int		status;
	char	*path;

	av = get_argv(node->args_list);
	if (!av || !av[0])
		return (free_tab(av), 0);
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
