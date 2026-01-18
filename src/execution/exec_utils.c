/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:30:00 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/18 19:30:00 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_argv(t_list *args)
{
	int		len;
	int		i;
	char	**new_args;

	len = ft_lstsize(args);
	i = 0;
	new_args = malloc(sizeof(char *) * (len + 1));
	if (!new_args)
		return (NULL);
	while (i < len)
	{
		new_args[i] = ft_strdup((char *)args->content);
		if (!new_args[i])
		{
			while (i > 0)
				free(new_args[--i]);
			free(new_args);
			return (NULL);
		}
		i++;
		args = args->next;
	}
	new_args[i] = 0;
	return (new_args);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*temp;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_minishell *shell)
{
	char	*path_var;
	char	**paths;
	char	*final_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	path_var = get_env_value("PATH", shell);
	if (!path_var || *path_var == '\0')
		return (ft_strdup(cmd));
	paths = ft_split(path_var, ':');
	if (!paths)
		return (ft_strdup(cmd));
	final_path = search_in_paths(paths, cmd);
	free_tab(paths);
	if (final_path)
		return (final_path);
	return (NULL);
}
