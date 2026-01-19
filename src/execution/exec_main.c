/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:39:29 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/19 17:39:08 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_logic(t_ast *node, t_minishell *shell)
{
	int	exit_code;

	exit_code = execute_ast(node->left, shell);
	if (node->type == NODE_AND && exit_code == 0)
		exit_code = execute_ast(node->right, shell);
	else if (node->type == NODE_OR && exit_code != 0)
		exit_code = execute_ast(node->right, shell);
	return (exit_code);
}

static int	exec_subshell(t_ast *node, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		shell->exit_code = execute_ast(node->left, shell);
		shell->is_child = 1;
		free_child(shell);
		exit(shell->exit_code);
	}
	ignore_signals();
	waitpid(pid, &status, 0);
	init_signals();
	return (get_exit_status(status));
}

static int	exec_redir_only(t_ast *node, t_minishell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	ret = handle_redirections(node->redirection);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (ret != 0)
		return (1);
	(void)shell;
	return (0);
}

static int	exec_simple_cmd(t_ast *node, t_minishell *shell)
{
	char	*cmd_name;

	if (node->args_list)
		cmd_name = (char *)node->args_list->content;
	else
		cmd_name = NULL;
	if (!cmd_name && node->redirection)
		return (exec_redir_only(node, shell));
	if (!cmd_name)
		return (0);
	if (is_builtin(cmd_name))
		return (exec_builtin(node, shell));
	return (exec_cmd(node, shell));
}

int	execute_ast(t_ast *node, t_minishell *shell)
{
	int	exit_code;

	if (!node)
		return (shell->exit_code);
	exit_code = 0;
	if (node->type == NODE_AND || node->type == NODE_OR)
		exit_code = exec_logic(node, shell);
	else if (node->type == NODE_PIPE)
		exit_code = exec_pipe(node, shell);
	else if (node->type == NODE_CMD)
		exit_code = exec_simple_cmd(node, shell);
	else if (node->type == NODE_SUBSHELL)
		exit_code = exec_subshell(node, shell);
	shell->exit_code = exit_code;
	return (exit_code);
}
