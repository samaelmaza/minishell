/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:56:47 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/15 22:05:30 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_content(void	*content)
{
	if (content)
		free(content);
}

void	clean_exit(t_minishell *shell, int exit_code)
{
	if (shell->token)
		free_token(&shell->token);
	if (shell->ast)
		free_ast(shell->ast);
	if (shell->env)
		ft_lstclear(&shell->env, free_content);
	rl_clear_history();
	exit(exit_code);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
