/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:20:47 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/09 19:29:34 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_delete_history_index(t_config *config, int idx)
{
	int len;

	len = (HISTORY_SIZE - idx) * sizeof(void *);
	ft_memmove(config->history + idx, config->history + idx + 1, len);
	ft_decr_history(&(config->hindex));
}

static void	ft_load_history_during_run(t_config *config)
{
	ft_load_history(config);
	ft_freegiveone((void **)&(config->hloc));
	config->hloc = ft_strdup(ft_return_hloc(NULL, 0));
}

static void	ft_purge_history_during_run(t_config *config)
{
	ft_purge_history(config, config->hist_newcmd, config->ncmd_index, 0);
	ft_strtabfree_content(config->hist_newcmd);
	ft_freegiveone((void **)&(config->hloc));
	config->hloc = ft_strdup(ft_return_hloc(NULL, 0));
}

void		ft_manage_param(char **argv, int i, t_config *config)
{
	int j;
	int idx;

	j = 0;
	while (argv[i][++j] && !ft_strisdigit(argv[i]))
	{
		if (argv[i][j] == 'c' && config->history[0] && !(config->hindex = 0))
			ft_strtabfree_content(config->history);
		else if (argv[i][j] == 'd' && argv[i + 1] && ft_strisdigit(argv[i + 1])
			&& ((idx = ft_atoi(argv[i + 1]) - 1) >= 0) && idx < HISTORY_SIZE)
			ft_delete_history_index(config, idx);
		else if (argv[i][j] == 'r')
			ft_load_history_during_run(config);
		else if (argv[i][j] == 'a')
			ft_purge_history_during_run(config);
		else if (ft_error("fc", "event not found", argv[i], CR_ERROR))
			return ;
	}
}
