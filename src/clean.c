/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:56:47 by sreffers          #+#    #+#             */
/*   Updated: 2025/12/08 15:59:24 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_content(void	*content)
{
	if(content)
		free(content);
}

void	clean_exit(t_minishell *shell, int exit_code)
{
	if(shell->env)
		ft_lstclear(&shell->env, free_content);
	exit(exit_code);
}
