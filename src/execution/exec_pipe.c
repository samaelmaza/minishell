/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:49:36 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/15 22:47:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	pipe_child_left(int *fd, t_ast *node, t_minishell *shell)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	shell->exit_code = execute_ast(node->left, shell);
	shell->is_child = 1;
	free_child(shell);
	exit(shell->exit_code);
}

static void	pipe_child_right(int *fd, t_ast *node, t_minishell *shell)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	shell->exit_code = execute_ast(node->right, shell);
	shell->is_child = 1;
	free_child(shell);
	exit(shell->exit_code);
}

static int	wait_for_children(pid_t pid_left, pid_t pid_right)
{
	int	status;

	ignore_signals();
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	init_signals();
	return (get_exit_status(status));
}

int	exec_pipe(t_ast *node, t_minishell *shell)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fd) == -1)
		return (perror("Pipe failed"), 1);
	pid_left = fork();
	if (pid_left == -1)
		return (perror("Fork failed"), 1);
	if (pid_left == 0)
		pipe_child_left(fd, node, shell);
	pid_right = fork();
	if (pid_right == -1)
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(pid_left, NULL, 0);
		return (perror("Fork failed"), 1);
	}
	if (pid_right == 0)
		pipe_child_right(fd, node, shell);
	close(fd[0]);
	close(fd[1]);
	return (wait_for_children(pid_left, pid_right));
}
