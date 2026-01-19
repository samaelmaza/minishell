/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:26:11 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/19 18:20:11 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_wildcard_match(t_list *current, char *new_str)
{
	char	**matches;

	matches = expand_wildcard(new_str);
	if (matches && matches[0])
	{
		insert_wildcard_matches(current, matches);
		free(new_str);
	}
	else
	{
		free_tab(matches);
		free(current->content);
		current->content = new_str;
	}
}

static void	expand_single_arg(t_list *current, t_minishell *shell)
{
	char	*old_str;
	char	*new_str;

	old_str = (char *)current->content;
	new_str = expand_string(old_str, shell);
	if (!new_str)
		return ;
	if (ft_strchr(new_str, '*'))
		handle_wildcard_match(current, new_str);
	else
	{
		free(old_str);
		current->content = new_str;
	}
}

static void	expand_args_list(t_list *args, t_minishell *shell)
{
	t_list	*current;

	current = args;
	while (current)
	{
		expand_single_arg(current, shell);
		current = current->next;
	}
	current = args;
	while (current)
	{
		restore_wildcards((char *)current->content);
		current = current->next;
	}
}

static void	expand_redirections(t_list *redirection, t_minishell *shell)
{
	t_redirection	*redir;
	char			*new_str;

	while (redirection)
	{
		redir = (t_redirection *)redirection->content;
		new_str = expand_string(redir->path, shell);
		if (new_str)
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
	if (node->type == NODE_CMD)
	{
		expand_args_list(node->args_list, shell);
		expand_redirections(node->redirection, shell);
	}
	expand_ast(node->left, shell);
	expand_ast(node->right, shell);
}
