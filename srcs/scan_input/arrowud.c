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

	if (stream->search)
		ft_searchengineend(stream);
	col = stream->col;
	while (col--)
		ft_left(stream);
}

void	ft_ctrldown(t_stream *stream)
{
	size_t		col;

	if (stream->search)
		ft_searchengineend(stream);
	col = stream->col;
	while (col--)
		ft_right(stream);
}
