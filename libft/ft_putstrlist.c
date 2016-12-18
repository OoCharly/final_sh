/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:32:40 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:32:51 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrlist(t_list *begin, char c)
{
	while (begin)
	{
		ft_putstr(begin->data);
		if (begin->next)
			ft_putchar(c);
		begin = begin->next;
	}
	ft_putchar('\n');
}
