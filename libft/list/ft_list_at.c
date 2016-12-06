/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/05 21:38:46 by tboos             #+#    #+#             */
/*   Updated: 2015/11/06 20:35:33 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "dclist.h"

t_dclist	*ft_dclist_at(t_dclist *begin_list, unsigned int nbr)
{
	if (nbr > 0 && begin_list)
		return (ft_dclist_at((begin_list)->next, nbr - 1));
	return (begin_list);
}

t_list		*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	if (nbr > 0 && begin_list)
		return (ft_list_at((begin_list)->next, nbr - 1));
	return (begin_list);
}
