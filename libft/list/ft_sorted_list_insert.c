/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <to-uss@noos.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 22:34:01 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:35:04 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "dclist.h"

static void	ft_msdclist(t_dclist **begin_list, t_dclist *new, t_dclist *turtle,
		t_dclist *rabbit)
{
	if (turtle)
	{
		turtle->next = new;
		new->prev = turtle;
	}
	else
	{
		new->prev = ft_dclist_last(*begin_list);
		*begin_list = new;
		new->prev->next = new;
	}
	new->next = rabbit;
	rabbit->prev = new;
}

void		ft_sorted_dclist_insert(t_dclist **begin_list, t_dclist *new,
		int (*cmp)())
{
	t_dclist	*rabbit;
	t_dclist	*turtle;
	t_dclist	*stop;

	if (new && !(*begin_list))
	{
		*begin_list = new;
		new->next = new;
		new->prev = new;
	}
	else if (new)
	{
		rabbit = *begin_list;
		stop = NULL;
		turtle = NULL;
		while (rabbit != stop && (*cmp)(new->data, rabbit->data) > 0)
		{
			stop = *begin_list;
			turtle = rabbit;
			rabbit = rabbit->next;
		}
		ft_msdclist(begin_list, new, turtle, rabbit);
	}
}

void		ft_sorted_list_insert(t_list **begin_list, t_list *new,
		int (*cmp)())
{
	t_list		*rabbit;
	t_list		*turtle;

	if (new)
	{
		rabbit = *begin_list;
		turtle = 0;
		while (rabbit && (*cmp)(new->data, rabbit->data) > 0)
		{
			turtle = rabbit;
			rabbit = rabbit->next;
		}
		if (turtle)
			turtle->next = new;
		else
			*begin_list = new;
		new->next = rabbit;
	}
}
