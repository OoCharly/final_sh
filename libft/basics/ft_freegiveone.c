/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freegiveone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 08:41:53 by tboos             #+#    #+#             */
/*   Updated: 2016/12/14 14:37:09 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free(void *kill)
{
	if (kill)
		free(kill);
	return (1);
}

int		ft_freegiveone(void **kill)
{
	if (kill && *kill)
	{
		free(*kill);
		*kill = NULL;
	}
	return (1);
}
