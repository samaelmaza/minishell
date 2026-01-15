/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:18:52 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/15 12:30:27 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if(!cmd)
		return (0);
	if(ft_strcmp(cmd, "echo") == 0)
		return (1);
	if(ft_strcmp(cmd, "cd") == 0)
		return (1);
	if(ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if(ft_strcmp(cmd, "export") == 0)
		return (1);
	if(ft_strcmp(cmd, "unset") == 0)
		return (1);
	if(ft_strcmp(cmd, "env") == 0)
		return (1);
	if(ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_ast *node, t_minishell *shell)
{
	char	**args;
	int		ret;

	args = get_argv(node->args_list);
	ret = 0;
	if(ft_strcmp(args[0], "echo") == 0)
		ret = ft_echo(args);
	else if(ft_strcmp(args[0], "pwd") == 0)
		ret = ft_echo(args);
	else if(ft_strcmp(args[0], "env") == 0)
		ret = ft_echo(args);
	free_tab(args);
	return (ret);
}
