/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:39:29 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/15 21:55:01 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_ast(t_ast *node, t_minishell *shell)
{
	int		exit_code;
	char	*cmd_name;

	if (!node)
		return (1);
	exit_code = 0;
	if (node->type == NODE_AND)
	{
		exit_code = execute_ast(node->left, shell);
		if (exit_code == 0)
			exit_code = execute_ast(node->right, shell);
	}
	else if (node->type == NODE_OR)
	{
		exit_code = execute_ast(node->left, shell);
		if (exit_code != 0)
			exit_code = execute_ast(node->right, shell);
	}
	else if (node->type == NODE_PIPE)
		exit_code = exec_pipe(node, shell);
	else if (node->type == NODE_CMD)
	{
		if (node->args_list)
			cmd_name = (char *)node->args_list->content;
		else
			cmd_name = NULL;
		if (cmd_name && is_builtin(cmd_name))
			exit_code = exec_builtin(node, shell);
		else
			exit_code = exec_cmd(node, shell);
	}
	shell->exit_code = exit_code;
	return (exit_code);
}
