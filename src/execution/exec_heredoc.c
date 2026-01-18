/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:37:00 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/18 13:37:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <fcntl.h>

static char	*get_heredoc_filename(void)
{
	static int	counter = 0;
	char		*num_str;
	char		*tmp;
	char		*filename;

	num_str = ft_itoa(counter++);
	if (!num_str)
		return (NULL);
	tmp = ft_strjoin("/tmp/.mini_heredoc_", num_str);
	free(num_str);
	if (!tmp)
		return (NULL);
	filename = ft_strjoin(tmp, "_tmp");
	free(tmp);
	return (filename);
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

static int	collect_single_heredoc(t_redirection *redir)
{
	int		fd;
	char	*filename;
	char	*old_path;

	filename = get_heredoc_filename();
	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(filename);
		perror("heredoc open");
		return (-1);
	}
	read_heredoc_lines(fd, redir->path);
	close(fd);
	old_path = redir->path;
	redir->path = filename;
	free(old_path);
	return (0);
}

static int	collect_heredocs_list(t_list *redirection)
{
	t_list			*tmp;
	t_redirection	*redir;

	tmp = redirection;
	while (tmp)
	{
		redir = (t_redirection *)tmp->content;
		if (redir->type == TOKEN_HEREDOC)
		{
			if (collect_single_heredoc(redir) != 0)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	collect_heredocs_ast(t_ast *node)
{
	if (!node)
		return (0);
	if (node->left)
	{
		if (collect_heredocs_ast(node->left) != 0)
			return (-1);
	}
	if (node->right)
	{
		if (collect_heredocs_ast(node->right) != 0)
			return (-1);
	}
	if (node->redirection)
	{
		if (collect_heredocs_list(node->redirection) != 0)
			return (-1);
	}
	return (0);
}
