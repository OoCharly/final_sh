/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_down.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:56:48 by tboos             #+#    #+#             */
/*   Updated: 2017/02/15 10:54:12 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_down_search(t_stream *stream)
{
	char	*com;
	size_t	len;

	com = stream->config->history[stream->config->hindex];
	len = ft_strlen(com);
	while (stream->shindex != stream->config->hindex
		&& stream->config->history[stream->shindex]
		&& ft_strncmp(com, stream->config->history[stream->shindex], len))
		ft_incr_history(NULL, &(stream->shindex));
}

void		ft_down(t_stream *stream)
{
	if (stream->search)
		ft_searchengine(stream);
	if (stream->shindex != stream->config->hindex)
	{
		ft_incr_history(NULL, &(stream->shindex));
		if (stream->config->history[stream->config->hindex]
			&& stream->config->history[stream->config->hindex][0])
			ft_down_search(stream);
		ft_gohome(stream);
		ft_freegiveone((void **)&(stream->command));
		if (stream->config->history[stream->shindex]
			&& (stream->command = stream->config->history[stream->shindex])
			&& !(stream->command = ft_strdup(stream->command))
			&& (stream->state = -2))
			return ;
		else
		{
			ft_winsize();
			ft_goend(stream);
		}
	}
	else
		ft_ringbell_fd(SFD);
}
