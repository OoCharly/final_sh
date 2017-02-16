/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:19:41 by rbaran            #+#    #+#             */
/*   Updated: 2017/02/16 11:35:41 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_job_done(t_config *config, char *description)
{
	t_list	*job;

	job = ft_extract_job(config, description);
	ft_putchar('\n');
	FT_PUTSTRFD(ft_st_itoa(*((int*)job->next->data)), "    ",
				"Done", 1);
	FT_PUTSTRFD("    ", ((t_sentence*)job->data)->sentence, "\n", 1);
	ft_free_all_process(&job, 1);
	ft_winsize();
}

static void	ft_job_suspended(t_list *job)
{
	ft_putchar('\n');
	((t_sentence*)((t_list*)job->data)->data)->state = SUSP;
	ft_print_jobs(NULL,
			((t_sentence*)((t_list*)(job->data))->data)->sentence);
	ft_print_jobs((t_list*)job->data, NULL);
	ft_winsize();
}

void		ft_jobs_manag(void)
{
	t_list		*list;
	t_config	*config;
	pid_t		pgid;
	int			status;

	config = ft_save_config(NULL);
	list = config->jobs;
	while (list)
	{
		status = 0;
		pgid = 0;
		if (((t_list*)list->data) && ((t_list*)list->data)->next)
			pgid = getpgid(*(pid_t*)(((t_list*)list->data)->next->data));
		if (pgid && waitpid(-pgid, &status, WNOHANG | WUNTRACED))
		{
			WIFSTOPPED(status) ? ft_job_suspended(list)
				: ft_job_done(config,
					((t_sentence*)((t_list*)(list->data))->data)->sentence);
			return ;
		}
		list = list->next;
	}
}

void		ft_process_manag(t_list **process, t_list *tmp, t_config *config)
{
	if (!process || !*process)
	{
		setpgid(*((pid_t*)tmp->data), *((pid_t*)tmp->data));
		if (DOT != 'b')
			tcsetpgrp(0, *((pid_t*)tmp->data));
		else if (config->script_state)
			signal(SIGTTOU, SIG_DFL);
	}
	else
		setpgid(*((pid_t*)tmp->data), *((pid_t*)(*process)->data));
	ft_list_push_back(process, tmp);
}
