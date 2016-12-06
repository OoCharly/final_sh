/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:55:20 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:14:39 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_signal_handle(int i)
{
	t_stream	*stream;

	if ((stream = ft_save_stream(NULL)) && stream->config)
	{
		if (i == SIGWINCH)
			ft_winsize();
		if (i == SIGINT)
		{
			if (stream->config->shell_state == RUNNING_COMMAND)
				stream->config->shell_state = SIGINT_COMMAND;
			else
			{
				stream->state = REPROMPT;
			}
		}
		if (i == SIGTSTP && stream->config->shell_state == RUNNING_COMMAND)
			stream->config->shell_state = SIGTSTP_COMMAND;
	}
	else
	{
		stream->config->shell_state = SIGINT_COMMAND;
		ft_error(SHNAME, NULL, "error while handling signal", CR_ERROR);
	}
	ft_signal(SIGNAL_SET);
}

static void	ft_scriptgnal_handle(int i)
{
	t_stream	*stream;

	dprintf(1, "on quitte proprement");
	(void)i;
	stream = ft_save_stream(NULL);
	ft_shell_exit(stream->config);
}

/*
**If terminal changes its size, caught the signal.
*/

void		ft_sigwinch(int mode)
{
	if (mode && SIG_ERR == signal(SIGWINCH, &ft_signal_handle))
		ft_error(SHNAME, NULL, "sigwinch fail", CR_ERROR);
	else if (!mode && SIG_ERR == signal(SIGWINCH, SIG_DFL))
		ft_error(SHNAME, NULL, "sigwinch fail", CR_ERROR);
}

int			ft_signal(int mode)
{
	if (mode == SIGNAL_SET)
	{
		if (SIG_ERR == signal(SIGINT, &ft_signal_handle))
			return (ft_status(1));
		if (SIG_ERR == signal(SIGTSTP, &ft_signal_handle))
			return (ft_status(1));
		return (0);
	}
	if (mode == SIGNAL_RESET)
	{
		if (SIG_ERR == signal(SIGINT, SIG_DFL))
			ft_status(1);
		if (SIG_ERR == signal(SIGTSTP, SIG_DFL))
			ft_status(1);
	}
	else if (mode == SIGNAL_SCRIPT)
	{
		if (SIG_ERR == signal(SIGINT, &ft_scriptgnal_handle)
				&& ft_error(SHNAME,
					"unable to set signal to stop without leeks", NULL, 1))
			ft_status(1);
	}
	return (0);
}
