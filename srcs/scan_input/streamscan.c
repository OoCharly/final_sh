/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streamscan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:02:50 by tboos             #+#    #+#             */
/*   Updated: 2017/02/16 22:00:59 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**When keys CTRL + D are touched, puts cursor on the first column after the
**prompt and exits the programe.
*/

static void	ft_ctrl_d(t_stream *stream)
{
	if ((stream->config)->heredoc)
	{
		stream->state = STR_EOF;
		return ;
	}
	ft_gohome(stream);
	ft_freegiveone((void**)&(stream->command));
	stream->command = ft_strdup("exit");
	ft_winsize();
	stream->state = REPROMPT;
}

static int	ft_clean_tabspeed(t_stream *stream)
{
	if (ft_isonlychr(stream->buf, '\t'))
		stream->buf[1] = 0;
	return (1);
}

static void	ft_scan(t_stream *stream)
{
	stream->shindex = stream->config->hindex;
	while (1)
	{
		ft_bzero(stream->buf, 255);
		if (((stream->ret = read(SFD, stream->buf, 255)) < 0
			&& (stream->state = -1))
			|| (stream->buf[0] == CTRLD
			&& (!stream->command || !stream->command[0]))
			|| (ft_clean_tabspeed(stream) && !ft_chrparse(stream)
			&& (!stream->command || stream->config->heredoc
			|| ft_quotecheck(stream))) || stream->state < 0)
			break ;
	}
	if (stream->config->term_state)
		ft_underline_mess(" ", stream);
}

static void	ft_pack_scan(t_stream *stream, t_config *config)
{
	ft_termios_handle(config, 1);
	if (config->heredoc && stream->command)
	{
		config->exclamation = ft_strchr(stream->command, '\n');
		if (config->exclamation && !(*(config->exclamation) = 0))
			config->exclamation = ft_strdup(config->exclamation + 1);
	}
	ft_winsize();
	ft_goend(stream);
	if (!stream->command || (!config->heredoc && !ft_pastereturn(stream)))
		ft_scan(stream);
	if (ft_freegiveone((void **)(&(stream->search))) && (stream->buf[0] == CTRLD
		|| (stream->state < 0 && ft_freegiveone((void **)(&(stream->command)))
		&& stream->state != REPROMPT
		&& ft_error(SHNAME, NULL, SCAN_ERR, CR_ERROR) && stream->state == -1)))
		ft_ctrl_d(stream);
	ft_putchar_fd('\n', SFD);
	ft_end_autocomp(stream);
	ft_sigwinch(0);
	ft_termios_handle(config, 0);
}

char		*ft_streamscan(t_config *config, t_stream *stream, int fd)
{
	ft_bzero(stream, sizeof(t_stream));
	ft_freegiveone((void **)(&(config->history[config->hindex])));
	stream->config = config;
	ft_strswap(&stream->command, &config->exclamation);
	SFD = fd;
	ft_pack_scan(stream, config);
	if (ft_is_memerizable(stream->command)
		&& !config->heredoc && stream->state != REPROMPT)
	{
		ft_push_history(stream, config);
		ft_incr_history(config, &(config->hindex));
	}
	return (stream->command);
}
