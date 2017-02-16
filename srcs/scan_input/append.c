/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 11:27:14 by cdesvern          #+#    #+#             */
/*   Updated: 2017/02/16 20:30:37 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_flushend(t_stream *stream)
{
	size_t		size;

	ft_repeat_termcaps(1, "cd", stream);
	if (stream->command[stream->pos])
	{
		if (stream->search)
			ft_flushsearch(stream);
		else if (stream->command && stream->command[0])
		{
			size = ft_strlen(stream->command + stream->pos);
			ft_putstr_fd(stream->command + stream->pos, SFD);
			stream->pos += size;
		}
		if (stream->pos && ft_checknewline(stream, stream->pos) == 0)
			ft_repeat_termcaps(1, "do", stream);
	}
	ft_erase(stream);
}

void			ft_flush(t_stream *stream)
{
	size_t		pos;

	pos = stream->pos;
	ft_flushend(stream);
	while (stream->pos != pos)
		ft_mvleft(stream);
}

void			ft_append(t_stream *stream)
{
	size_t		pos;
	size_t		len;
	char		*kill;

	len = ft_strlen(stream->buf);
	if ((kill = stream->command))
	{
		pos = stream->pos;
		if (!(stream->command = ft_strnew(ft_strlen(stream->command) + len))
				&& (stream->state = -2) && ft_freegiveone((void **)&kill))
			return ;
		ft_strncpy(stream->command, kill, pos);
		ft_strcpy(stream->command + pos, stream->buf);
		ft_strcpy(stream->command + pos + len, kill + pos);
		ft_freegiveone((void **)&kill);
	}
	else if (!(stream->command = ft_strdup(stream->buf)))
		stream->state = -2;
	ft_push_history(stream, stream->config);
	ft_flush(stream);
	while (len--)
		ft_mvright(stream);
}
