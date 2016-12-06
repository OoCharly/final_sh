/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/06 21:46:25 by tboos             #+#    #+#             */
/*   Updated: 2016/09/28 17:04:33 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "dclist.h"

static void	ft_dcdelete_if(t_dclist *rabbit, void *data_ref, int (*cmp)(),
			void (*ft_free)())
{
	t_dclist	*turtle;
	t_dclist	*memo;

	memo = rabbit->prev;
	while (rabbit != memo)
	{
		if ((*cmp)(rabbit->data, data_ref) == 0)
		{
			rabbit = rabbit->next;
			rabbit->prev = turtle;
			ft_free(turtle->next->data);
			free(turtle->next);
			turtle->next = rabbit;
		}
		else
		{
			turtle = rabbit;
			rabbit = rabbit->next;
		}
	}
}

void		ft_dclist_remove_if(t_dclist **begin_list, void *data_ref,
			int (*cmp)(), void (*ft_free)())
{
	t_dclist	*rabbit;

	if (begin_list && *begin_list)
	{
		while (*begin_list && cmp((*begin_list)->data, data_ref) == 0)
		{
			rabbit = *begin_list;
			*begin_list = (*begin_list)->next;
			rabbit->prev->next = *begin_list;
			(*begin_list)->prev = rabbit->prev;
			ft_free(rabbit);
			if (rabbit == *begin_list)
				*begin_list = NULL;
		}
		if (*begin_list)
			ft_dcdelete_if(*begin_list, data_ref, cmp, ft_free);
	}
}

static void	ft_delete_if(t_list **rabbit, void *data_ref, int (*cmp)(),
			void (*ft_free)())
{
	t_list	*turtle;

	while (*rabbit)
	{
		if ((*cmp)((*rabbit)->data, data_ref) == 0)
		{
			*rabbit = (*rabbit)->next;
			ft_free(turtle->next);
			turtle->next = *rabbit;
		}
		else
		{
			turtle = *rabbit;
			*rabbit = (*rabbit)->next;
		}
	}
}

void		ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
			void (*ft_free)())
{
	t_list	*rabbit;

	if (begin_list && *begin_list)
	{
		while (*begin_list && !cmp((*begin_list)->data, data_ref))
		{
			rabbit = *begin_list;
			(*begin_list) = (*begin_list)->next;
			ft_free(rabbit);
		}
		rabbit = *begin_list;
		ft_delete_if(&rabbit, data_ref, cmp, ft_free);
	}
}
