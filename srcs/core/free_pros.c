/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pros.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:52:24 by tboos             #+#    #+#             */
/*   Updated: 2017/01/07 00:41:16 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freepros(t_list *kill)
{
	free(kill->data);
	free(kill);
}

void	ft_free_one_process(t_list **process, pid_t pid)
{
	ft_list_remove_if(process, (void*)&pid, ft_proscmp, ft_freepros);
	if (!(*process) || ((*process)->data_size == SENT && !(*process)->next))
		if (*process)
		{
			free((*process)->data);
			free(*process);
			*process = NULL;
		}
}

void	ft_free_all_process(t_list **process, int mode)
{
	t_list *tmp;

	while (*process)
	{
		tmp = *process;
		if (tmp->data_size == SENT)
		{
			free(((t_sentence*)tmp->data)->sentence);
			if (((t_sentence*)tmp->data)->supervisor_pid)
				kill(((t_sentence*)(tmp->data))->supervisor_pid, SIGQUIT);
			free(tmp->data);
		}
		else if (mode)
			kill(*((pid_t*)(tmp->data)), SIGINT);
		(*process) = (*process)->next;
		free(tmp);
	}
}

void	ft_free_all_jobs(t_list **job)
{
	t_list *tmp;

	while (*job)
	{
		tmp = *job;
		ft_free_all_process(((t_list **)&(tmp->data)), 1);
		(*job) = (*job)->next;
		free(tmp);
	}
}
