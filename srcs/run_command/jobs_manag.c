/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_manag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:19:41 by rbaran            #+#    #+#             */
/*   Updated: 2017/02/27 12:44:12 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_checksignal(int stat_loc, int *signum)
{
	if ((WIFSIGNALED(stat_loc) && WTERMSIG(stat_loc)))
	{
		*signum = WTERMSIG(stat_loc);
		return (1);
	}
	if ((WIFSTOPPED(stat_loc) && WSTOPSIG(stat_loc)))
	{
		*signum = WSTOPSIG(stat_loc);
		return (2);
	}
	return (0);
}

static int		ft_checkjob(t_list *processes, int *signum)
{
	int		stat_loc;
	pid_t	proc_pid;
	int		ret;

	ret = 0;
	while (processes)
	{
		stat_loc = 0;
		proc_pid = *((pid_t*)processes->data);
		if (!waitpid(proc_pid, &stat_loc, WNOHANG | WUNTRACED))
			ret = -1;
		if (ft_checksignal(stat_loc, signum))
			return (ft_checksignal(stat_loc, signum));
		processes = processes->next;
	}
	return (ret);
}

static void		ft_print_job_state(t_list *job, int signum, int kill)
{
	char	*state;

	state = NULL;
	if (job)
	{
		if (!(state = ft_get_signalerr(signum, state))
					&& !(state = ft_get_signalsusp(signum, state)))
			state = "Done";
		ft_putchar('\n');
		FT_PUTSTRFD(ft_st_itoa(*((int*)job->next->data)), "    ",
					((t_sentence*)job->data)->sentence, 1);
		FT_PUTSTRFD("    ", (state) ? state : "Unknown", "\n", 1);
		if (kill)
			ft_free_all_process(&job, 1);
	}
}

static t_list	*ft_job_state(t_list *job, t_config *config, int status_pgid)
{
	t_list	*next;
	int		signum;
	int		check;

	next = job->next;
	signum = 0;
	if ((check = ft_checksignal(status_pgid, &signum))
		|| -1 != (check = ft_checkjob(((t_list*)job->data)->next, &signum)))
	{
		if (check == 0 || (check == 1 && (check = 1)))
			job = ft_extract_job(config,
					((t_sentence*)((t_list*)job->data)->data)->sentence);
		else if (!(check = 0))
		{
			job = (t_list*)job->data;
			((t_sentence*)job->data)->state = SUSP;
		}
		ft_print_job_state(job, signum, check);
	}
	return (next);
}

void			ft_jobs_manag(t_config *config)
{
	t_list		*list;
	pid_t		pgid;
	int			status;

	list = config->jobs;
	while (list)
	{
		status = 0;
		pgid = 0;
		if (((t_list*)list->data) && ((t_list*)list->data)->next)
			pgid = getpgid(*(pid_t*)(((t_list*)list->data)->next->data));
		if (pgid && waitpid(-pgid, &status, WNOHANG | WUNTRACED))
			list = ft_job_state(list, config, status);
		else
			list = list->next;
	}
	if (config->shell_state == SCANNING_COMMAND
			|| config->shell_state == SIGTSTP_COMMAND)
		ft_winsize();
}
