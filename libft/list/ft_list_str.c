/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:30:12 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:30:14 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_list_strlen(t_list *begin)
{
	size_t	len;

	len = 0;
	while (begin)
	{
		if (begin->data)
			len += ft_strlen((char *)begin->data);
		begin = begin->next;
	}
	return (len);
}
