/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:18:52 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/16 22:29:39 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static int	run_builtin(char **args, t_minishell *shell)
{
	char	*cmd;

	cmd = args[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(shell));
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(args, shell));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(args, shell));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(args, shell));
	return (0);
}

int	exec_builtin(t_ast *node, t_minishell *shell)
{
	char	**args;
	int		ret;
	int		saved_stdin;
	int		saved_stdout;

	args = get_argv(node->args_list);
	if (!args)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (node->redirection && handle_redirections(node->redirection) != 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		free_tab(args);
		return (1);
	}
	ret = run_builtin(args, shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	free_tab(args);
	if (shell->is_child)
	{
		free_child(shell);
		exit(ret);
	}
	return (ret);
}
