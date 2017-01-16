/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 17:40:06 by maxpetit          #+#    #+#             */
/*   Updated: 2017/01/16 14:01:27 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_visselect(t_stream *stream)
{
	char	c;
	size_t	pos;

	ft_winsize();
	pos = stream->pos;
	ft_putstr_fd(ANSI_REVERSEVID, SFD);
	ft_gomatch(stream, VISUAL_AT_RIGHT ? stream->visual_pos : pos + 1);
	c = stream->command[VISUAL_AT_RIGHT ? pos : stream->visual_pos];
	stream->command[VISUAL_AT_RIGHT ? pos : stream->visual_pos] = 0;
	ft_flushend(stream);
	stream->command[VISUAL_AT_RIGHT ? pos : stream->visual_pos] = c;
	ft_putstr_fd(ANSI_COLOR_RESET, SFD);
	ft_flushend(stream);
	ft_gomatch(stream, pos);
}

void	ft_viscut(t_stream *stream)
{
	int		i;
	size_t	pos;
	char	*rabbit;

	pos = stream->pos;
	FREE((void **)&stream->config->visual_buf);
	stream->config->visual_buf = ft_strsub(stream->command,
		VISUAL_AT_RIGHT ? stream->visual_pos : pos,
		VISUAL_AT_RIGHT ? pos - stream->visual_pos : stream->visual_pos - pos);
	rabbit = (VISUAL_AT_RIGHT ? stream->command + pos
		: stream->command + stream->visual_pos);
	i = (VISUAL_AT_RIGHT ? stream->visual_pos : pos);
	ft_memmove(stream->command + i, rabbit, ft_strlen(rabbit) + 1);
	stream->visual = 0;
	ft_winsize();
	stream->visual_pos = stream->pos;
}

void	ft_viscopy(t_stream *stream)
{
	size_t pos;

	pos = stream->pos;
	FREE((void **)&stream->config->visual_buf);
	stream->config->visual_buf = ft_strsub(stream->command,
		VISUAL_AT_RIGHT ? stream->visual_pos : pos,
		VISUAL_AT_RIGHT ? pos - stream->visual_pos : stream->visual_pos - pos);
	stream->visual = 0;
	ft_winsize();
	stream->visual_pos = stream->pos;
}

void	ft_vispaste(t_stream *stream)
{
	int		len;
	char	*rabbit;

	if (stream->config->visual_buf)
	{
		rabbit = stream->config->visual_buf;
		while (*rabbit)
		{
			ft_strncpy(stream->buf, rabbit, 255);
			ft_append(stream);
			len = ft_strlen(rabbit);
			rabbit += (len > 255 ? 255 : len);
		}
		stream->visual_pos = stream->pos;
	}
}
