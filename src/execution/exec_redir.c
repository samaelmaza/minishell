/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:49:00 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/18 13:37:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>

static int	open_redir_fd(t_redirection *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == TOKEN_INPUT)
		fd = open(redir->path, O_RDONLY);
	else if (redir->type == TOKEN_HEREDOC)
	{
		fd = open(redir->path, O_RDONLY);
		if (fd != -1)
			unlink(redir->path);
	}
	else if (redir->type == TOKEN_TRUNC)
		fd = open(redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_APPEND)
		fd = open(redir->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	handle_redirections(t_list *redirection)
{
	t_list			*tmp;
	t_redirection	*redir;
	int				fd;

	tmp = redirection;
	while (tmp)
	{
		redir = (t_redirection *)tmp->content;
		fd = open_redir_fd(redir);
		if (fd == -1)
			return (perror("minishell"), 1);
		if (redir->type == TOKEN_INPUT || redir->type == TOKEN_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}
