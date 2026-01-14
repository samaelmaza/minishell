#include "../../include/minishell.h"
#include <fcntl.h>

static int	handle_heredoc(char *delimiter)
{
	int		fd;
	char	*line;
	char	*filename = "/tmp/.mini_heredoc_tmp";
	int		stdin_backup;
	int		stdout_backup; // <-- NOUVEAU
	int		fd_tty;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc open"), -1);

	// 1. Sauvegardes
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO); // <-- NOUVEAU

	// 2. Forcer l'entrée ET la sortie sur le TTY
	fd_tty = open("/dev/tty", O_RDWR); // <-- O_RDWR (Lecture ET Ecriture)
	if (fd_tty != -1)
	{
		dup2(fd_tty, STDIN_FILENO);
		dup2(fd_tty, STDOUT_FILENO); // <-- Le prompt ira à l'écran !
		close(fd_tty);
	}

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

	// 3. Restaurations
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO); // <-- On remet la redirection fichier
	close(stdin_backup);
	close(stdout_backup); // <-- N'oublie pas de close le backup
	close(fd);

	fd = open(filename, O_RDONLY);
	unlink(filename);
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
		fd = -1;
		if (redir->type == TOKEN_INPUT)
			fd = open(redir->path, O_RDONLY);
		else if (redir->type == TOKEN_HEREDOC)
			fd = handle_heredoc(redir->path);
		else if (redir->type == TOKEN_TRUNC)
			fd = open(redir->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == TOKEN_APPEND)
			fd = open(redir->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("minishell");
			return (1);
		}
		if (redir->type == TOKEN_INPUT || redir->type == TOKEN_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}
