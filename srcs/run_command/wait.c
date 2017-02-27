/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 12:56:00 by tboos             #+#    #+#             */
/*   Updated: 2017/02/27 16:48:10 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_abord_signal(int signum, pid_t pid, t_list **proc)
{
	char		*err;
	char		*str;

	err = NULL;
	if ((err = ft_get_signalerr(signum, err)) && (*proc)->data_size == SENT
		&& (str = ft_strchrjoin(ft_st_itoa(pid), ' ',
				((t_sentence*)(*proc)->data)->sentence))
		&& ft_error(SHNAME, str, err, CR_ERROR) && ft_freegiveone((void**)&str))
		return (true);
	else if (err && ft_error(SHNAME, ft_st_itoa(pid), err, CR_ERROR))
	{
		if (str)
			ft_freegiveone((void**)&str);
		return (true);
	}
	return (false);
}

static int	ft_handle_pid_return(t_list **process, t_config *config,
		int stat_loc, pid_t pid)
{
	if (WIFEXITED(stat_loc))
	{
		ft_free_one_process(process, pid);
		config->last_exit = WEXITSTATUS(stat_loc);
	}
	else if (WIFSIGNALED(stat_loc))
	{
		if (ft_abord_signal(WTERMSIG(stat_loc), pid, process)
			&& (config->last_exit = 4))
		{
			ft_free_all_process(process, 1);
			return (0);
		}
		else
			ft_free_one_process(process, pid);
	}
	return (1);
}

static int	ft_wait(t_list **process, t_config *config)
{
	int		stat_loc;
	pid_t	pid;
	pid_t	yolo_pgid;

	config->last_exit = 0;
	yolo_pgid = (*process && (*process)->next) ?
		-((*(pid_t*)((*process)->next->data))) : 0;
	while (process && *process)
	{
		stat_loc = 0;
		pid = waitpid(yolo_pgid, &stat_loc, WNOHANG | WUNTRACED);
		if (pid < 0 || config->shell_state == SIGINT_COMMAND)
		{
			ft_free_all_process(process, 1);
			config->last_exit = 1;
			return (0);
		}
		else if ((!pid && config->shell_state == SIGTSTP_COMMAND
					&& (config->shell_state = RUNNING_COMMAND))
				|| WIFSTOPPED(stat_loc))
			return (1);
		else if (pid && !ft_handle_pid_return(process, config, stat_loc, pid))
			return (0);
	}
	return (0);
}

void		ft_wait_sentence(t_list *job, t_config *config)
{
	t_list		*new;
	t_sentence	*new_sent;

	if ((config->fg_sentence)
		&& (((!(new_sent = (t_sentence*)ft_memalloc(sizeof(*new_sent))))
		|| (!(new_sent->sentence = config->fg_sentence)))
		|| (!(new = ft_lstnew((void*)new_sent, SENT))
		&& ft_freegiveone((void **)&new_sent)))
		&& ft_freegiveone((void **)&config->fg_sentence))
		ft_error(SHNAME, "parser", "malloc error on process control", CR_ERROR);
	else if (config->fg_sentence && !(config->fg_sentence = NULL))
		ft_list_push_front(&job, new);
	if ((DOT == 'b' || ft_wait(&job, config)))
	{
		(((t_sentence*)new->data)->state = (DOT == 'b') ? RUN : SUSP);
		if (!(new = ft_lstnew((void*)job, JOB)))
		{
			ft_error(SHNAME, "parser", "malloc error on job control", CR_ERROR);
			ft_free_all_process(&job, 1);
		}
		else
			ft_list_push_front(&(config->jobs), new);
	}
	tcsetpgrp(0, config->shell_pgid);
}
