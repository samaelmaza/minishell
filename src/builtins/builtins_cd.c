/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:07:32 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/19 17:31:56 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_wds(t_minishell *shell)
{
	char	cwd[1024];
	char	*tmp;

	if (getcwd(cwd, sizeof(cwd)))
	{
		tmp = ft_strjoin("PWD=", cwd);
		update_env(shell, tmp);
		free(tmp);
	}
}

static char	*get_cd_target(char **args, t_minishell *shell)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_value("HOME", shell);
		if (!path)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (path);
	}
	if (ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value("OLDPWD", shell);
		if (!path)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		else
			printf("%s\n", path);
		return (path);
	}
	return (args[1]);
}

static void	update_cd_env(t_minishell *shell, char *old_pwd)
{
	char	*export_old;

	export_old = ft_strjoin("OLDPWD=", old_pwd);
	if (export_old)
	{
		update_env(shell, export_old);
		free(export_old);
	}
	update_wds(shell);
}

int	ft_cd(char **args, t_minishell *shell)
{
	char	*path;
	char	old_pwd[1024];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	path = get_cd_target(args, shell);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	update_cd_env(shell, old_pwd);
	return (0);
}
