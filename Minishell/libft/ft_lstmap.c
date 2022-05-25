/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:40:07 by aoumad            #+#    #+#             */
/*   Updated: 2021/12/02 13:50:02 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*lst_new;
	t_list	*new;

	if (lst && f)
	{
		lst_new = ft_lstnew(f(lst->content));
		if (!lst_new)
			return (NULL);
		new = lst_new;
		while (lst->next)
		{		
			lst = lst->next;
			new->next = ft_lstnew(f(lst->content));
			if (!new->next)
			{
				ft_lstclear(&lst_new, del);
				return (NULL);
			}
			new = new->next;
		}
		return (lst_new);
	}
	return (NULL);
}
