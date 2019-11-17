/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youkhart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:31:33 by youkhart          #+#    #+#             */
/*   Updated: 2019/10/20 18:05:51 by youkhart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_bonus.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;

	if (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
			return (0);
		head = new;
		while (lst)
		{
			lst = lst->next;
			if (!lst)
				break ;
			if (!(new->next = ft_lstnew(f(lst->content))))
			{
				ft_lstclear(&head, del);
				return (0);
			}
			new = new->next;
		}
		return (head);
	}
	else
		return (0);
}
