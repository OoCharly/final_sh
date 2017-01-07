/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowud.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:16 by tboos             #+#    #+#             */
/*   Updated: 2016/12/13 11:55:14 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Moves cursor on the last colum.
*/

void	ft_goend(t_stream *stream)
{
	if (stream->command)
		while (stream->command[stream->pos])
			ft_mvright(stream);
}

/*
**Moves cursor on the first column after the prompt.
*/

void	ft_gohome(t_stream *stream)
{
	while (stream->pos)
		ft_mvleft(stream);
}

void	ft_ctrlup(t_stream *stream)
{
	size_t		col;
	size_t		mem;

	if (stream->search)
		ft_searchengineend(stream);
	col = ft_checknewline(stream, stream->pos);
	mem = col;
	while (col--)
		ft_left(stream);
	ft_left(stream);
	col = ft_checknewline(stream, stream->pos);
	while (col-- > mem)
		ft_left(stream);
}

void	ft_ctrldown(t_stream *stream)
{
	size_t		col;
	size_t		mem;

	if (stream->search)
		ft_searchengineend(stream);
	if (stream->pos)
	{
		col = ft_checknewline(stream, stream->pos);
		mem = col;
		while (col++ < stream->col)
		{
			ft_right(stream);
			if (stream->command[stream->pos] == '\n')
				col = stream->col - 1;
		}
		col = ft_checknewline(stream, stream->pos);
		while (col++ < mem && stream->command[stream->pos] != '\n')
			ft_right(stream);
	}
}
