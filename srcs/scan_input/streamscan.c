/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   streamscan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:02:50 by tboos             #+#    #+#             */
/*   Updated: 2016/12/12 16:40:08 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Copies the current terminal attributes in config->termios and
**config->termios_backup. Changes the control mode in non canonical and stop
**echo of input characters. Defines a minimun of zero characters for
**noncanonical read. No defines a timeout for noncanonical read.
*/

static int	ft_init_term(t_config *config)
{
	if (tcgetattr(STDIN_FILENO, &(config->termios_backup)) == -1
		|| !ft_memcpy(&(config->termios), &(config->termios_backup),
		sizeof(t_termios)))
		return (1 ^ ft_error(SHNAME, NULL, TERM_ERR, CR_ERROR));
	config->termios.c_lflag &= ~(ICANON | ECHO);
	config->termios.c_cc[VMIN] = 0;
	config->termios.c_cc[VTIME] = 1;
	return (true);
}

/*
**For the first call of function gets terminal attributes and Changes
**config->termios. If mode exists, modification of term attributes occurs after
**all output written to STDIN_FILENO has been transmitted. If mode doesn't
**exists, modification are set immediately.
*/

static void	ft_termios_handle(t_config *config, int mode)
{
	static char		state = 0;

	if (!state && ft_init_term(config))
		state = 1;
	if (mode && state
		&& (tcsetattr(STDIN_FILENO, TCSADRAIN, &(config->termios)) == -1))
		ft_error(SHNAME, NULL, TERM_ERR, CR_ERROR);
	else if (!mode && state
		&& (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &(config->termios_backup))))
		ft_error(SHNAME, NULL, RESET_TERM_ERR, CR_ERROR);
	return ;
}

/*
**When keys CTRL + D are touched, puts cursor on the first column after the 
**prompt and exits the programe.
*/

static void	ft_ctrl_d(t_stream *stream)
{
	ft_gohome(stream);
	ft_freegiveone((void**)&(stream->command));
	stream->command = ft_strdup("exit");
	ft_winsize();
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
			|| (!ft_chrparse(stream) && (!stream->command
			|| stream->config->heredoc || ft_quotecheck(stream)))
			|| stream->state < 0)
			break ;
	}
	if (stream->config->term_state)
		ft_underline_mess(" ", stream);
}

char		*ft_streamscan(t_config *config, t_stream *stream, int fd)
{
	ft_bzero(stream, sizeof(t_stream));
	ft_freegiveone((void **)(&(config->history[config->hindex])));
	stream->config = config;
	SFD = fd;
	ft_termios_handle(config, 1);
	ft_winsize();
	ft_scan(stream);
	ft_sigwinch(0);
	ft_termios_handle(config, 0);
	ft_freegiveone((void **)(&(stream->search)));
	if (stream->buf[0] == CTRLD
		|| (stream->state < 0 && ft_freegiveone((void **)(&(stream->command)))
		&& stream->state != REPROMPT
		&& ft_error(SHNAME, NULL, SCAN_ERR, FCR_ERROR) && stream->state == -1))
		ft_ctrl_d(stream);
	if (stream->command && stream->command[0] && (!config->hindex
		|| ft_strcmp(stream->command, config->history[config->hindex - 1]))
		&& !config->heredoc && stream->state != REPROMPT)
	{
		ft_push_history(stream, config, 0);
		ft_incr_history(&(config->hindex));
	}
	ft_putchar_fd('\n', SFD);
	return (stream->command);
}
