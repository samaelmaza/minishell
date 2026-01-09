/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:26:11 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 19:10:37 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_args_list(t_list *args, t_minishell *shell)
{
	char	*old_str;
	char	*new_str;

	while(args)
	{
		old_str = (char *)args->content;
		new_str = expand_string(old_str, shell);
		if(new_str)
		{
			free(old_str);
			args->content = new_str;
		}
		args = args->next;
	}
}

static void expand_redirections(t_list *redirection, t_minishell *shell)
{
	t_redirection	*redir;
	char			*new_str;

	while(redirection)
	{
		redir = (t_redirection *)redirection->content;
		new_str = expand_string(redir->path, shell);
		if(new_str)
		{
			free(redir->path);
			redir->path = new_str;
		}
		redirection = redirection->next;
	}
}

void	expand_ast(t_ast *node, t_minishell *shell)
{
	if (!node)
		return ;
	if(node->type == NODE_CMD)
	{
		expand_args_list(node->args_list, shell);
		expand_redirections(node->redirection, shell);
	}
	expand_ast(node->left, shell);
	expand_ast(node->right, shell);
}
