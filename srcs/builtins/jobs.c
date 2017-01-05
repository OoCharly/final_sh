/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:45:29 by tboos             #+#    #+#             */
/*   Updated: 2017/01/05 15:14:51 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_extract_job(t_config *config, char *description)
{
	int		i;
	t_list	*p;
	t_list	*m;

	p = config->jobs;
	i = 1;
	if (!description || ft_cmp_jobs(p->data, description, i))
	{
		m = (t_list*)p->data;
		config->jobs = p->next;
		free(p);
		return (m);
	}
	while ((m = p)
			&& (p = p->next) && ++i)
	{
		if (ft_cmp_jobs(p->data, description, i))
		{
			m->next = p->next;
			m = (t_list*)p->data;
			free(p);
			return (m);
		}
	}
	return (NULL);
}

static void		ft_continue(t_config *config, char *description, int mode)
{
	t_list	*p;
	t_list	*target;

	if (!(config->jobs))
		ft_error(mode == JOBS_FG ? "fg" : "bg", NULL, "no current jobs",
				CR_ERROR);
	else if (!(target = ft_extract_job(config, description)))
		ft_error(mode == JOBS_FG ? "fg" : "bg", description, "no such job",
				CR_ERROR);
	else if (mode == JOBS_FG)
	{
		p = target;
		while ((p = p->next))
			kill(*((pid_t*)p->data), SIGCONT);
		ft_freegiveone((void**)&config->fg_sentence);
		ft_wait_sentence(target, config);
	}
}

void			ft_jobs(char **argv, t_config *config)
{
	size_t	i;

	i = 1;
	ft_print_jobs(NULL, argv[i]);
	if (!config->jobs)
	{
		ft_error("jobs", NULL, "no current job", CR_ERROR);
		return ;
	}
	else if (!argv[i])
		ft_lstiter(config->jobs, ft_print_list);
	else
		while (argv[i++])
		{
			ft_lstiter(config->jobs, ft_print_list);
			ft_print_jobs(NULL, argv[i]);
		}
}

void			ft_fgbg(char **argv, t_config *config, int mode)
{
	size_t	i;

	i = (argv[0][0] == '%' ? 0 : 1);
	if (!argv[i])
		ft_continue(config, NULL, mode);
	else
		while (argv[i])
			ft_continue(config, argv[i++], mode);
}
