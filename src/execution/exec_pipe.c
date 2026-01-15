/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:49:36 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/14 11:38:46 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pipe(t_ast *node, t_minishell *shell)
{
	int	fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	int		exit_code;

	if(pipe(fd) == -1)
	{
		perror("Pipe failed");
		return (1);
	}
	pid_left = fork();
	if(pid_left == -1)
	{
		perror("Fork failed");
		return (1);
	}
	if(pid_left == 0)
	{
		shell->is_child = 1;
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		shell->exit_code = execute_ast(node->left, shell);
		free_child(shell);
		exit(shell->exit_code);
	}
	pid_right = fork();
	if(pid_right == -1)
	{
		perror("Fork failed");
		return (1);
	}
	if(pid_right == 0)
	{
		shell->is_child = 1;
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		shell->exit_code = execute_ast(node->right, shell);
		free_child(shell);
		exit(shell->exit_code);
	}
	close(fd[0]);
	close(fd[1]);
	ignore_signals();
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	init_signals();
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = 128;
	return (exit_code);
}
