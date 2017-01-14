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
	char	c;
	size_t	pos;

	pos = stream->pos;
	ft_putstr_fd(ANSI_REVERSEVID, SFD);
	if (pos > stream->visual_pos)
	{
		ft_gomatch(stream, stream->visual_pos);
		c = stream->command[pos];
		stream->command[pos] = 0;
		ft_flushend(stream);
		stream->command[pos] = c;
	}
	else if (pos < stream->visual_pos)
	{
		ft_gomatch(stream, pos);
		c = stream->command[stream->visual_pos];
		stream->command[stream->visual_pos] = 0;
		ft_flushend(stream);
		stream->command[stream->visual_pos] = c;
	}
	ft_putstr_fd(ANSI_COLOR_RESET, SFD);
	ft_flushend(stream);
	ft_gomatch(stream, pos);
}

void	ft_viscut(t_stream *stream)
{
	(void)stream;
}

void	ft_viscopy(t_stream *stream)
{
	(void)stream;
}

void	ft_vispaste(t_stream *stream)
{
	(void)stream;
}
