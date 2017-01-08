/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrsed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 16:25:40 by tboos             #+#    #+#             */
/*   Updated: 2017/01/08 16:25:42 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strchrsed(char *str, char origin, char target)
{
	while (str && *str)
	{
		if (*str == origin)
			*str = target;
		++str;
	}
}
