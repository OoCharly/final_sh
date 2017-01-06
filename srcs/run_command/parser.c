/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:18:53 by tboos             #+#    #+#             */
/*   Updated: 2017/01/06 19:09:17 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_cut_lst(t_list *begin, t_config *config)
{
	t_list	*memo;

	while (begin)
	{
		memo = begin;
		begin = begin->next;
		if (begin && begin->data_size
			&& (!ft_strcmp(";", (char*)(begin->data))
			|| !ft_strcmp("&&", (char*)(begin->data))
			|| !ft_strcmp("||", (char*)(begin->data))))
		{
			config->dot_sequence = ((char*)(begin->data))[0];
			begin = begin->next;
			free(memo->next->data);
			ft_freegiveone((void **)&(memo->next));
			break ;
		}
	}
	return (begin);
}

int				ft_build_pipe(t_list *begin, t_config *config, int **r_pipe)
{
	t_list	*rhead;

	while (begin && begin->data_size && begin->data_size != SSHELL)
		begin = begin->next;
	if (begin && begin->next)
	{
		rhead = begin->next;
		if (!ft_node_descriptors(begin, &rhead, config, r_pipe))
			return (0);
		if (begin->next)
			begin->next->next = rhead;
		else
			begin->next = rhead;
	}
	return (1);
}

static void		ft_sentence(t_list *begin, t_config *config)
{
	t_list	*job;
	int		*r_pipe;

	ft_build_sentence(begin, config);
	r_pipe = NULL;
	if (!ft_build_pipe(begin, config, &r_pipe))
		return ;
	if ((job = ft_run_sentence(begin, config, r_pipe)))
		ft_wait_sentence(job, config);
	ft_freegiveone((void**)&r_pipe);
	ft_freegiveone((void**)&config->fg_sentence);
}

void			ft_parse(t_config *config)
{
	char	test;

	config->last_exit = 0;
	test = ';';
	while ((config->chimera_tail = ft_cut_lst(config->chimera, config)))
	{
		if ((config->shell_state == RUNNING_COMMAND
			|| config->shell_state == RUNNING_SSHELL)
			&& (test == ';' || (test == '&' && !config->last_exit)
			|| (test == '|' && config->last_exit)))
			ft_sentence(config->chimera, config);
		ft_freelist(&config->chimera);
		config->chimera = config->chimera_tail;
		test = config->dot_sequence;
	}
	if ((config->shell_state == RUNNING_COMMAND
		|| config->shell_state == RUNNING_SSHELL)
		&& (test == ';' || (test == '&' && !config->last_exit)
		|| (test == '|' && config->last_exit)))
		ft_sentence(config->chimera, config);
	ft_freelist(&config->chimera);
}
