/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             */
/*   Updated: 2016/11/29 14:14:04 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dclist	*ft_dclstnew(void *data, size_t data_size)
{
	t_dclist	*new;

	if (!(new = (t_dclist *)malloc(sizeof(t_dclist))))
		return (NULL);
	ft_bzero(new, sizeof(t_dclist));
	if (data)
	{
		new->data_size = data_size;
		new->data = data;
	}
	return (new);
}

t_list		*ft_lstnew(void *data, size_t data_size)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	ft_bzero(new, sizeof(t_list));
	if (data)
	{
		new->data_size = data_size;
		new->data = data;
	}
	new->next = NULL;
	return (new);
}
