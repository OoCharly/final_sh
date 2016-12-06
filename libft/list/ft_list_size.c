/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/05 15:26:51 by tboos             #+#    #+#             */
/*   Updated: 2016/10/28 17:14:13 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "dclist.h"

size_t	ft_dclist_size(t_dclist *begin_list)
{
	size_t		size;
	t_dclist	*stop;

	size = 1;
	if (!(stop = begin_list))
		return (0);
	while (begin_list->next)
	{
		begin_list = begin_list->next;
		size++;
		if (begin_list == stop)
			return (size);
	}
	return (size);
}

size_t	ft_list_size(t_list *begin_list)
{
	size_t	size;

	size = 1;
	if (begin_list == NULL)
		return (0);
	while (begin_list->next)
	{
		begin_list = begin_list->next;
		size++;
	}
	return (size);
}
