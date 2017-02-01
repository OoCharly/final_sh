/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:55:20 by tboos             #+#    #+#             */
/*   Updated: 2017/02/01 11:14:57 by rbaran           ###   ########.fr       */
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
				ft_freegiveone((void**)&stream->config->exclamation);
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

	(void)i;
	stream = ft_save_stream(NULL);
	ft_shell_exit(stream->config);
}

static void	ft_dass(int status)
{
	t_list		*list;
	t_config	*config;
	pid_t		pgid;

	config = ft_save_config(NULL);
	list = config->jobs;
	while (list)
	{
		status = 0;
		pgid = 0;
		if (((t_list*)list->data) && ((t_list*)list->data)->next)
			pgid = getpgid(*(pid_t*)(((t_list*)list->data)->next->data));
		if (pgid && waitpid(-pgid, &status, WNOHANG | WUNTRACED) && WIFSTOPPED(status))
		{
			((t_sentence*)((t_list*)list->data)->data)->state = SUSPENDED;
			FT_PUTSTRFD(ft_st_itoa(*((int*)((t_list*)(list->data))->next->data)), "    ",
				((t_sentence*)((t_list*)(list->data))->data)->state == RUNNING ?
										"Running" : "Suspended", 1);
			FT_PUTSTRFD("    ", ((t_sentence*)((t_list*)(list->data))->data)->sentence, "\n", 1);

		}
		list = list->next;
	}
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
		if (SIG_ERR == signal(SIGTTOU, SIG_IGN))
			return (ft_status(1));
		if (SIG_ERR == signal(SIGCHLD, &ft_dass))
			return (ft_status(1));
		return (0);
	}
	if (mode == SIGNAL_RESET)
	{
		if (SIG_ERR == signal(SIGINT, SIG_DFL))
			ft_status(1);
		if (SIG_ERR == signal(SIGTSTP, SIG_DFL))
			ft_status(1);
		if (SIG_ERR == signal(SIGTTOU, SIG_DFL))
			ft_status(1);
		if (SIG_ERR == signal(SIGCHLD, SIG_DFL))
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
