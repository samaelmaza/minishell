/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:49:00 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/15 22:47:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>

static void	setup_tty(int *stdin_backup, int *stdout_backup)
{
	int	fd_tty;

	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	fd_tty = open("/dev/tty", O_RDWR);
	if (fd_tty != -1)
	{
		dup2(fd_tty, STDIN_FILENO);
		dup2(fd_tty, STDOUT_FILENO);
		close(fd_tty);
	}
}

static void	restore_fds(int stdin_backup, int stdout_backup, int fd)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	close(fd);
}

static int	read_heredoc_lines(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0
			&& ft_strlen(delimiter) == ft_strlen(line))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

static int	handle_heredoc(char *delimiter)
{
	int		fd;
	char	*filename;
	int		stdin_backup;
	int		stdout_backup;

	filename = "/tmp/.mini_heredoc_tmp";
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc open"), -1);
	setup_tty(&stdin_backup, &stdout_backup);
	read_heredoc_lines(fd, delimiter);
	restore_fds(stdin_backup, stdout_backup, fd);
	fd = open(filename, O_RDONLY);
	unlink(filename);
	return (fd);
}

static int	open_redir_fd(t_redirection *redir)
{
	if (redir->type == TOKEN_INPUT)
		return (open(redir->path, O_RDONLY));
	else if (redir->type == TOKEN_HEREDOC)
		return (handle_heredoc(redir->path));
	else if (redir->type == TOKEN_TRUNC)
		return (open(redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (redir->type == TOKEN_APPEND)
		return (open(redir->path, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
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
