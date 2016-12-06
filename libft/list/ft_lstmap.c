/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:31:07 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "dclist.h"

t_dclist		*ft_dclstmap(t_dclist *lst, t_dclist *(*f)(t_dclist *elem))
{
	t_dclist	*cpy;
	t_dclist	*rabbit;
	t_dclist	*turtle;
	t_dclist	*stop;

	cpy = NULL;
	if ((stop = lst))
	{
		if (!(cpy = f(lst)))
			return (NULL);
		lst = lst->next;
	}
	rabbit = cpy;
	while (lst != stop)
	{
		turtle = rabbit;
		if (!(rabbit = f(lst)))
			return (NULL);
		turtle->next = rabbit;
		rabbit->prev = turtle;
		lst = lst->next;
	}
	cpy->prev = rabbit;
	rabbit->next = cpy;
	return (cpy);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*cpy;
	t_list		*rabbit;
	t_list		*turtle;

	cpy = NULL;
	if (lst)
	{
		cpy = f(lst);
		if (!(cpy = ft_lstnew(cpy->data, cpy->data_size)))
			return (NULL);
		lst = lst->next;
	}
	rabbit = cpy;
	while (lst)
	{
		turtle = rabbit;
		rabbit = f(lst);
		if (!(rabbit = ft_lstnew(rabbit->data, rabbit->data_size)))
			return (NULL);
		turtle->next = rabbit;
		lst = lst->next;
	}
	return (cpy);
}
