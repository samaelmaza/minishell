/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:54:19 by sreffers          #+#    #+#             */
/*   Updated: 2025/10/01 23:39:39 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_lst;

	new_lst = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new);
		lst = lst->next;
	}
	return (new_lst);
}

/*#include <stdio.h>

void	*duplicate_content(void *content)
{
	char	*str = (char *)content;
	return (ft_strdup(str));
}

void	delete_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*lst = NULL;
	t_list	*new_lst;
	t_list	*tmp;

	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Hello")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("World")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("42")));

	new_lst = ft_lstmap(lst, duplicate_content, delete_content);

	printf("Original list:\n");
	tmp = lst;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}

	printf("\nMapped list:\n");
	tmp = new_lst;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}

	ft_lstclear(&lst, delete_content);
	ft_lstclear(&new_lst, delete_content);

	return (0);
}*/
