/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:39:29 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 23:52:40 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_ast(t_ast *node, t_minishell *shell)
{
	int	exit_code;

	exit_code = 0;
	if(!node)
		return (1);
	// if(node->type == NODE_AND || node->type == NODE_OR)
	// 	exit_code = exec_logic(node, shell);
	// if(node->type == NODE_PIPE)
	// 	exit_code = exec_pipe(node, shell);
	if(node->type == NODE_CMD)
		exit_code = exec_cmd(node, shell);
	shell->exit_code = exit_code;
	return (exit_code);
}
