/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:39:29 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/15 22:47:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_logic_and(t_ast *node, t_minishell *shell)
{
	int	exit_code;

	exit_code = execute_ast(node->left, shell);
	if (exit_code == 0)
		exit_code = execute_ast(node->right, shell);
	return (exit_code);
}

static int	exec_logic_or(t_ast *node, t_minishell *shell)
{
	int	exit_code;

	exit_code = execute_ast(node->left, shell);
	if (exit_code != 0)
		exit_code = execute_ast(node->right, shell);
	return (exit_code);
}

static int	exec_simple_cmd(t_ast *node, t_minishell *shell)
{
	char	*cmd_name;

	if (node->args_list)
		cmd_name = (char *)node->args_list->content;
	else
		cmd_name = NULL;
	if (cmd_name && is_builtin(cmd_name))
		return (exec_builtin(node, shell));
	return (exec_cmd(node, shell));
}

int	execute_ast(t_ast *node, t_minishell *shell)
{
	int	exit_code;

	if (!node)
		return (1);
	exit_code = 0;
	if (node->type == NODE_AND)
		exit_code = exec_logic_and(node, shell);
	else if (node->type == NODE_OR)
		exit_code = exec_logic_or(node, shell);
	else if (node->type == NODE_PIPE)
		exit_code = exec_pipe(node, shell);
	else if (node->type == NODE_CMD)
		exit_code = exec_simple_cmd(node, shell);
	shell->exit_code = exit_code;
	return (exit_code);
}
