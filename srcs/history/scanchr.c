/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 12:20:30 by rbaran            #+#    #+#             */
/*   Updated: 2016/11/14 08:57:45 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_modifycommand(t_stream *stream)
{
	ft_gohome(stream);
	ft_freegiveone((void **)&(stream->command));
	if (stream->config->history[stream->shindex])
		stream->command = ft_strdup(stream->config->history[stream->shindex]);
	else if (stream->config->history[stream->config->hindex])
		stream->command = ft_strdup(
				stream->config->history[stream->config->hindex]);
	else
		stream->command = (char*)ft_memalloc(1);
	ft_winsize();
	ft_sprompt(stream);
	if (!stream->pos)
		ft_goend(stream);
}

void		ft_sappend(t_stream *stream)
{
	char	*kill;

	if ((kill = stream->search))
	{
		stream->search = ft_strjoin(stream->search, stream->buf);
		ft_freegiveone((void**)&kill);
		stream->shindex = stream->config->hindex;
		ft_searchinhistory(stream);
		ft_modifycommand(stream);
	}
}

void		ft_sdel(t_stream *stream)
{
	if (stream->search && stream->search[0])
	{
		stream->search[ft_strlen(stream->search) - 1] = '\0';
		stream->shindex = stream->config->hindex;
		if (stream->search && stream->search[0])
			ft_searchinhistory(stream);
		ft_modifycommand(stream);
	}
}
