/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:26:11 by sreffers          #+#    #+#             */
/*   Updated: 2026/01/09 18:16:09 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"





char *expand_string(char *str, t_minishell *shell)
{
	int		i;
	int		j;
	char	*expanded;

	i = 0;
	j = 0;
	expanded = malloc(sizeof(char) * (get_expand_line(str, shell) + 1));
	if (!expanded)
		return (NULL);


}
