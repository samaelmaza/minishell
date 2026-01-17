/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 21:26:18 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/14 11:28:13 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_redir(void *content)
{
	t_redirection	*redir;

	redir = (t_redirection *)content;
	if (!redir)
		return ;
	if (redir->path)
		free(redir->path);
	free(redir);
}

void	free_token(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (!token || !*token)
		return ;
	current = *token;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	del_content(void *content)
{
	if (content)
		free(content);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->args_list)
		ft_lstclear(&node->args_list, del_content);
	if (node->redirection)
		ft_lstclear(&node->redirection, free_redir);
	free(node);
}

void	free_child(t_minishell *shell)
{
	if (shell->ast)
		free_ast(shell->ast);
	if (shell->token)
		free_token(&shell->token);
	if (shell->env)
		ft_lstclear(&shell->env, del_content);
	rl_clear_history();
}
