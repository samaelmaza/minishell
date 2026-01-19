/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreffers <sreffers@student.42madrid.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 11:43:51 by sreffers          #+#    #+#             */
/*   Updated: 2025/10/01 15:50:51 by sreffers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
}

/*void print_list(t_list *lst)
{
    while (lst)
    {
        printf("%s -> ", (char *)lst->data);
        lst = lst->next;
    }
    printf("NULL\n");
}

int main(void)
{
    t_list *list = NULL;

    ft_lstadd_back(&list, ft_lstnew("first"));
    print_list(list);

    ft_lstadd_back(&list, ft_lstnew("second"));
    ft_lstadd_back(&list, ft_lstnew("third"));
    print_list(list);

    return (0);
}


void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list **current = lst;
	if(!lst || !new)
		return;
	while((*current))
	{
		current=&(*current)->next;
	}
	*current = new;
}*/
