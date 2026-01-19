/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 22:07:32 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/19 15:47:57 by sreffers         ###   ########.fr       */
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

int	ft_cd(char **args, t_minishell *shell)
{
	char	*path;
	char	old_pwd[1024];
	char	*export_old;

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	if (!args[1])
	{
		path = get_env_value("HOME", shell);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if(ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value("OLDPWD", shell);
		if(!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		printf("%s\n", path);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	export_old = ft_strjoin("OLDPWD=", old_pwd);
	update_env(shell, export_old);
	free(export_old);
	update_wds(shell);
	return (0);
}
