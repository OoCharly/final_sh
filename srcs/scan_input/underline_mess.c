/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underline_mess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:18:09 by tboos             #+#    #+#             */
/*   Updated: 2017/01/09 01:24:52 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putmess(t_stream *stream, char *mess)
{
	size_t			i;

	ft_goend(stream);
	ft_putchar_fd('\n', SFD);
	ft_repeat_termcaps(1, "cd", stream);
	ft_putstr_fd(mess, SFD);
	if (ft_strlen(mess) % stream->col == 0)
		ft_putchar_fd('\n', SFD);
	ft_putchar_fd('\n', SFD);
	i = ft_strlen(mess) / stream->col;
	ft_repeat_termcaps(i + 2, "up", stream);
	i = ft_checknewline(stream, stream->pos);
	ft_repeat_termcaps(i, "nd", stream);
}

int			ft_underline_mess(char *mess, t_stream *stream)
{
	size_t			pos_buf;

	pos_buf = stream->pos;
	ft_putmess(stream, mess);
	ft_gomatch(stream, pos_buf);
	return (0);
}
