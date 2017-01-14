/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchengine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 12:07:27 by rbaran            #+#    #+#             */
/*   Updated: 2017/01/12 17:37:35 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_searchinhistory(t_stream *stream)
{
	ft_decr_history(&(stream->shindex));
	while (stream->shindex != stream->config->hindex
		&& stream->config->history[stream->shindex]
		&& !(ft_strstr(stream->config->history[stream->shindex],
			stream->search)))
		ft_decr_history(&(stream->shindex));
}

void		ft_searchengineend(t_stream *stream)
{
	int	index;

	index = -1;
	if (stream->search)
	{
		if (stream->command && stream->search[0])
			index = ft_strstri(stream->command, stream->search);
		ft_freegiveone((void**)&(stream->search));
		stream->search = NULL;
		ft_winsize();
		if (index != -1)
			ft_gomatch(stream, (size_t)index);
	}
	else
	{
		stream->visual ^= 1;
		stream->visual_pos = stream->pos;
		ft_winsize();
	}
}

void		ft_searchengine(t_stream *stream)
{
	ft_gohome(stream);
	if (!(stream->search))
	{
		stream->search = ft_strnew(1);
		ft_sprompt(stream);
	}
	else
	{
		ft_searchinhistory(stream);
		ft_modifycommand(stream);
	}
}
