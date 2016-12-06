/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/05 23:40:00 by tboos             #+#    #+#             */
/*   Updated: 2015/12/16 21:56:41 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "dclist.h"

void	ft_dclist_merge(t_dclist **begin_list1, t_dclist *begin_list2)
{
	t_dclist	*rabbit;

	if (begin_list1 && *begin_list1 && begin_list2)
	{
		rabbit = ft_dclist_last(*begin_list1);
		rabbit->next = begin_list2;
		rabbit->next->prev = rabbit;
		rabbit = ft_dclist_last(begin_list2);
		rabbit->next = *begin_list1;
		rabbit->next->prev = rabbit;
	}
	else if (begin_list1 && begin_list2)
		*begin_list1 = begin_list2;
}

void	ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list	*rabbit;

	if (begin_list1 && *begin_list1 && begin_list2)
	{
		rabbit = *begin_list1;
		while (rabbit->next)
			rabbit = rabbit->next;
		rabbit->next = begin_list2;
	}
	else if (begin_list1 && begin_list2)
		*begin_list1 = begin_list2;
}
