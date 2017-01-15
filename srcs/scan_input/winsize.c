/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:44:56 by tboos             #+#    #+#             */
/*   Updated: 2017/01/09 04:00:21 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_secure_prompt(t_stream *stream)
{
	ft_repeat_termcaps(1, "cd", stream);
	ft_prompt(stream->config);
	if (!((stream->config->prompt_len) % stream->col))
		ft_repeat_termcaps(1, "do", stream);
	if (stream->search)
		ft_sprompt(stream);
}

/*
**Fill stream->row and stream->col with winsize structure w wich contents screen
**width and height (in characters).
*/

void			ft_prompt_reset(t_stream *stream)
{
	struct winsize	w;
	size_t			col;
	size_t			lin;

	ioctl(SFD, TIOCGWINSZ, &w);
	col = w.ws_col;
	if (stream->visual && stream->col != col)
		stream->visual = 2;
	stream->row = w.ws_row;
	if (stream->col)
	{
		lin = PROMPT_LEN / (stream->col > col ? stream->col : col);
		ft_gohome(stream);
		ft_putchar_fd('\n', SFD);
		ft_repeat_termcaps(lin + 1, "up", stream);
	}
	stream->col = col;
	ft_secure_prompt(stream);
}

void			ft_flush_command(t_stream *stream)
{
	unsigned int	pos;

	pos = stream->pos;
	if (stream->command)
	{
		stream->pos = 0;
		ft_flushend(stream);
	}
	ft_gomatch(stream, pos);
}

void			ft_winsize(void)
{
	t_stream		*stream;
	size_t			pos;

	stream = ft_save_stream(NULL);
	pos = stream->pos;
	ft_prompt_reset(stream);
	ft_flush_command(stream);
	ft_gomatch(stream, pos);
	if (COMP_STATE)
		ft_comp_print(stream);
	else if (stream->search)
		ft_sprompt(stream);
	if (stream->command && stream->visual == 2)
	{
		stream->visual = 1;
		ft_visselect(stream);
	}
	ft_sigwinch(1);
}
