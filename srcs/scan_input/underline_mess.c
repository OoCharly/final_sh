/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underline_mess.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:18:09 by tboos             #+#    #+#             */
/*   Updated: 2017/01/02 17:07:57 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putmess(t_stream *stream, char *mess)
{
	size_t			i;

	ft_putstr_fd(mess, SFD);
	if (!((stream->pos + stream->config->prompt_len) % stream->col))
	{
		ft_putstr_fd(" ", SFD);
		stream->tput = "le";
		ft_tputs(stream);
	}
	stream->tput = "le";
	i = stream->col;
	while (i--)
		ft_tputs(stream);
	i = ft_strlen(mess) / stream->col + 1;
	stream->tput = "up";
	while (i--)
		ft_tputs(stream);
}

int		ft_underline_mess(char *mess, t_stream *stream)
{
	int			i;
	unsigned int	pos_buf;

	pos_buf = stream->pos;
	ft_goend(stream);
	ft_repeat_termcaps(1, "do", stream);
	ft_repeat_termcaps(stream->col, "le", stream);
	stream->tput = "cd";
	ft_tputs(stream);
	ft_putmess(stream, mess);
	i = ft_checknewline(stream, stream->pos);
	ft_repeat_termcaps(i < 0 ? -i : i, "nd", stream);
	ft_gomatch(stream, pos_buf);
	return (0);
}
