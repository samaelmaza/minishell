/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:19:42 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/12 23:38:33 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_redirections(t_list	*redirection)
{
	t_list			*tmp;
	int				fd;
	t_redirection	*redir;

	tmp = redirection;
	while(tmp)
	{
		redir = tmp->content;
		if(redir->type == TOKEN_INPUT)
		{
			fd = open(redir->path, O_RDONLY);
			if(fd == -1)
			{
				perror("minishell");
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if(redir->type == TOKEN_TRUNC)
		{
			fd = open(redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd == -1)
			{
				perror("minishell");
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if(redir->type == TOKEN_APPEND)
		{
			fd = open(redir->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if(fd == -1)
			{
				perror("minishell");
				return (1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
	return (0);
}


