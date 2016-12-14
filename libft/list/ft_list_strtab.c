/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_strtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 14:27:21 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/14 14:29:14 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_list_strtab(t_list *begin)
{
	char	**tab;
	size_t	size;
	int		i;

	tab = NULL;
	if (begin)
	{
		size = ft_list_size(begin);
		if (!(tab = (char**)ft_memalloc(sizeof(void*) * (size + 1))))
			return (NULL);
		i = -1;
		while (++i < (int)size && begin)
		{
			tab[i] = begin->data;
			begin = begin->next;
		}
	}
	return (tab);
}
