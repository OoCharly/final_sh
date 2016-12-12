/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:27:08 by tboos             #+#    #+#             */
/*   Updated: 2016/12/12 16:40:25 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_erase(t_stream *stream)
{
	stream->tput = "dc";
	ft_tputs(stream);
}

void	ft_clean_field(t_stream *stream)
{
	ft_goend(stream);
	while (stream->pos)
	{
		ft_left(stream);
		ft_erase(stream);
	}
}

void	ft_del(t_stream *stream)
{
	size_t	pos;

	if (stream->search)
		ft_sdel(stream);
	else if (stream->command && stream->pos)
	{
		ft_mvleft(stream);
		pos = stream->pos - 1;
		while (stream->command[++pos])
			stream->command[pos] = stream->command[pos + 1];
		stream->tput = "cd";
		ft_tputs(stream);
		ft_flush(stream);
		ft_push_history(stream, stream->config, 1);
	}
}

void	ft_sup(t_stream *stream)
{
	size_t	i;
	size_t	pos;

	if (stream->command && stream->command[stream->pos])
	{
		i = -1;
		pos = stream->pos;
		while (stream->command[pos + ++i])
			stream->command[pos + i] = stream->command[pos + i + 1];
		stream->tput = "cd";
		ft_tputs(stream);
		ft_flush(stream);
		ft_push_history(stream, stream->config, 1);
	}
}
