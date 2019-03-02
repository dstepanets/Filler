/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:09:48 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/13 18:09:50 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*cur;

	if (lst && f)
	{
		if (!(new_lst = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		new_lst = f(lst);
		cur = new_lst;
		while (lst->next)
		{
			lst = lst->next;
			cur->next = f(lst);
			if (cur->next == NULL)
				return (NULL);
			cur = cur->next;
		}
		return (new_lst);
	}
	return (NULL);
}
