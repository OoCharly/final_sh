/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowlr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:06 by tboos             #+#    #+#             */
/*   Updated: 2016/09/21 13:50:00 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_left(t_stream *stream)
{
	if (stream->search)
		ft_searchengine(stream);
	if (stream->pos)
		ft_mvleft(stream);
}

void	ft_right(t_stream *stream)
{
	if (stream->search)
		ft_searchengine(stream);
	if (stream->command && ft_strlen(stream->command) != stream->pos)
		ft_mvright(stream);
}

void	ft_ctrlleft(t_stream *stream)
{
	if (stream->search)
		ft_searchengine(stream);
	ft_left(stream);
	while (stream->command && stream->pos
		&& !(!ft_isspace(stream->command[stream->pos])
		&& ft_isspace(stream->command[stream->pos - 1])))
		ft_mvleft(stream);
}

void	ft_ctrlright(t_stream *stream)
{
	if (stream->search)
		ft_searchengine(stream);
	ft_right(stream);
	while (stream->command && stream->command[stream->pos]
		&& !(!ft_isspace(stream->command[stream->pos])
		&& stream->command[stream->pos] != '\0'
		&& ft_isspace(stream->command[stream->pos - 1])))
		ft_mvright(stream);
}
