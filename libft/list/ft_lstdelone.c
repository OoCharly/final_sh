/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             */
/*   Updated: 2016/02/22 20:32:17 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "dclist.h"

void	ft_dclstdelone(t_dclist **alst, void (*del)(void *, size_t))
{
	if (alst && *alst)
	{
		if (del)
			del((*alst)->data, (*alst)->data_size);
		free(*alst);
		*alst = NULL;
	}
}

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (alst && *alst)
	{
		if (del)
			del((*alst)->data, (*alst)->data_size);
		free(*alst);
		*alst = NULL;
	}
}
