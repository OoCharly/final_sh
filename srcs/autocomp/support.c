/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:44:31 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:05:44 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Delete list. Set COMP_STATE back to 0.
*/

void	ft_end_autocomp(t_stream *stream)
{
	size_t pos_buf;

	reset_autocomp(stream);
	pos_buf = stream->pos;
	COMP_STATE = 0;
	ft_goend(stream);
	stream->tput = "cd";
	ft_tputs(stream);
	ft_gomatch(stream, pos_buf);
}

/*
** Parse key to know if have to exit.
** True if status is left unchanged.
*/

int		ft_is_same_autocomp(t_stream *stream)
{
	static ssize_t	match[] = {LEF, RIG, UPP, DOW, CHT, SHCHT};
	int				i;
	int				is_same;

	i = -1;
	is_same = 0;
	if (COMP_STATE && ((ssize_t*)stream->buf)[0])
	{
		while (match[++i])
			if (((ssize_t*)(stream->buf))[0] == match[i])
				is_same = (i == 4) ? 2 : 1;
		if (!is_same)
			ft_end_autocomp(stream);
		else if ((COMP_STATE == 1 || COMP_STATE == 0) && is_same != 2)
			ft_end_autocomp(stream);
		else
			return (1);
	}
	return (0);
}

/*
** Free list for exit.
** Reinitialize struct autocomp.
*/

void	reset_autocomp(t_stream *stream)
{
	ft_lstdel(&(COMP_BEGIN_LIST), ft_list_free_data);
	ft_freegiveone((void**)&(COMP_BEGIN));
	ft_bzero(&(stream->comp), sizeof(t_comp));
}

/*
** Execute termcaps "term" n time.
*/

void	ft_repeat_termcaps(size_t time, char *term, t_stream *stream)
{
	size_t i;

	i = time;
	stream->tput = term;
	while (i--)
		ft_tputs(stream);
}

/*
** Compare list size with terminal size.
*/

int		ft_autocomp_is_oversize(t_stream *stream)
{
	size_t	command_size;
	size_t	clen;

	clen = ft_strlen(stream->command);
	command_size = (stream->config->prompt_len + clen) % COMP_COL;
	command_size = (command_size) ?
	(stream->config->prompt_len + clen) / COMP_COL + 1 :
	(stream->config->prompt_len + clen) / COMP_COL;
	if (COMP_IN_COL > (COMP_DISPLAYABLE = COMP_ROW - command_size))
		return (1);
	return (0);
}
