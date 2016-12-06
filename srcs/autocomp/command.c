/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:34:56 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:01:02 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Mode = 'D' -> Set cursor on next line.
** Mode = 'U' -> Set cursor back to initial position.
*/

void		ft_autocomp_underline(t_stream *stream, char mode)
{
	size_t				i;
	static unsigned int	pos_buf;

	if (mode == 'D')
	{
		pos_buf = stream->pos;
		ft_goend(stream);
		stream->tput = "do";
		ft_tputs(stream);
		ft_repeat_termcaps(stream->col, "le", stream);
		stream->tput = "cd";
		ft_tputs(stream);
	}
	else
	{
		i = (stream->command) ? stream->config->prompt_len +
			ft_strlen(stream->command) : stream->config->prompt_len;
		i = i % stream->col;
		ft_repeat_termcaps(i, "nd", stream);
		ft_gomatch(stream, pos_buf);
	}
}

/*
** Put command back to initial state before autocomp call.
*/

void		ft_autocomp_delete(t_stream *stream)
{
	char	*kill;
	size_t	len;

	ft_gohome(stream);
	stream->tput = "cd";
	ft_tputs(stream);
	len = ft_strlen(COMP_BUF);
	if ((kill = stream->command))
	{
		if (!(stream->command = ft_strnew(ft_strlen(stream->command) - len)))
			return ;
		ft_strncpy(stream->command, kill, COMP_POS_COMMAND);
		ft_strcpy(stream->command + COMP_POS_COMMAND,
				kill + COMP_POS_COMMAND + len);
		ft_putstr_fd(stream->command, SFD);
		stream->pos += (ft_strlen(stream->command) % stream->col);
		ft_freegiveone((void**)&kill);
	}
	ft_gomatch(stream, COMP_POS_COMMAND);
}

/*
** Modified version of append calling specific buffer name COMP_BUF.
*/

void		ft_autocomp_append(t_stream *stream)
{
	size_t				pos;
	size_t				len;
	char				*kill;

	len = ft_strlen(COMP_BUF);
	if ((kill = stream->command))
	{
		pos = stream->pos;
		if (!(stream->command = ft_strnew(ft_strlen(stream->command) + len))
				&& (stream->state = -2) && ft_freegiveone((void **)&kill))
			return ;
		ft_strncpy(stream->command, kill, pos);
		ft_strcpy(stream->command + pos, COMP_BUF);
		ft_strcpy(stream->command + pos + len, kill + pos);
		ft_freegiveone((void **)&kill);
	}
	else if (!(stream->command = ft_strdup(COMP_BUF)))
		stream->state = -2;
	ft_push_history(stream, stream->config);
	ft_flush(stream);
	while (len--)
		ft_mvright(stream);
}
