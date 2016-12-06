/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:02 by tboos             #+#    #+#             */
/*   Updated: 2016/11/14 08:52:14 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shell_exit(t_config *config)
{
	ft_free_config(config);
	exit(ft_status(0));
}

void	ft_freebin(void *data, size_t data_size)
{
	if (data_size)
	{
		free(((t_bin *)data)->path_name);
		free(data);
	}
}

void	ft_free_config(t_config *config)
{
	if (config)
	{
		ft_free_all_jobs(&(config->jobs));
		ft_freegiveone((void **)&(config->pwd));
		if (config->env)
			ft_strtabfree(config->env);
		if (config->bin)
			ft_lstdel(&(config->bin), &ft_freebin);
		if (config->hloc)
			ft_purge_history(config);
		else
			ft_strtabfree(config->history);
		if (config->hloc)
			free(config->hloc);
		ft_freelist(&config->chimera);
		ft_freelist(&config->chimera_tail);
		ft_freegiveone((void**)&config->command);
		ft_freegiveone((void**)&config->fg_sentence);
		get_next_line(-1, NULL);
	}
}
