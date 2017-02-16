/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:42:15 by tboos             #+#    #+#             */
/*   Updated: 2017/02/16 17:25:12 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_status(int value)
{
	static int	status = 0;

	if (value == 666)
		status = 0;
	else if (value)
	{
		status = value;
		return (1);
	}
	return (status);
}
