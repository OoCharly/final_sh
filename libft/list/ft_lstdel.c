/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             */
/*   Updated: 2016/12/14 14:25:27 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"
#include "dclist.h"

void	ft_list_free_data(void *data, size_t data_size)
{
	data_size = 0;
	(void)data_size;
	ft_freegiveone((void **)&data);
}

int		ft_dclstdel_err(t_dclist **alst, void (*del)(void *, size_t))
{
	ft_dclstdel(alst, (*del));
	return (-1);
}

void	ft_dclstdel(t_dclist **alst, void (*del)(void *, size_t))
{
	t_dclist	*tmp;
	t_dclist	*stop;

	if (alst)
		stop = *alst;
	tmp = NULL;
	while (alst && *alst && tmp != stop)
	{
		tmp = (*alst)->next;
		ft_dclstdelone(alst, del);
		*alst = tmp;
	}
	*alst = NULL;
}

int		ft_lstdel_err(t_list **alst, void (*del)(void *, size_t))
{
	ft_lstdel(alst, (*del));
	return (-1);
}

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*tmp;
	t_list		*kill;

	if (alst)
	{
		kill = *alst;
		*alst = NULL;
		while (kill)
		{
			tmp = kill->next;
			ft_lstdelone(&kill, del);
			kill = tmp;
		}
	}
}
