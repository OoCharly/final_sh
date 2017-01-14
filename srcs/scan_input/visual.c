/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:40:06 by maxpetit          #+#    #+#             */
/*   Updated: 2017/01/12 18:10:43 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_visselect(t_stream *stream)
{
	dprintf(SFD, "OOOOOO");
	if (stream->visual)
	{
		ft_putstr_fd(ft_itoa(stream->pos), SFD);
	}
}

void	ft_viscut(t_stream *stream)
{
	if (stream->visual)
	{
	}
}

void	ft_viscopy(t_stream *stream)
{
	if (stream->visual)
	{
	}
}

void	ft_vispaste(t_stream *stream)
{
	if (stream->visual)
	{
	}
}
