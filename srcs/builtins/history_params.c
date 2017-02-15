/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:20:47 by maxpetit          #+#    #+#             */
/*   Updated: 2017/02/15 16:26:03 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_delete_history_index(t_config *config, int idx)
{
	int len;

	len = (HISTORY_SIZE - idx) * sizeof(void *);
	ft_freegiveone((void **)config->history + idx);
	ft_memmove(config->history + idx, config->history + idx + 1, len);
	ft_decr_history(config, &(config->hindex));
}

static void	ft_load_history_during_run(t_config *config)
{
	int ret;

	if ((((ret = ft_count_line_file(config)) == -1)
		|| ret + config->hindex > HISTORY_SIZE)
		&& ft_error(SHNAME, NULL, "full history", CR_ERROR)
		&& ft_freegiveone((void **)&(config->hlocbis)))
		return ;
	ft_load_history(config);
	ft_freegiveone((void **)&(config->hlocbis));
}

static void	ft_stock_cmd(t_config *config, char **argv, int i)
{
	int len;
	int total_len;
	int j;

	j = -1;
	len = 0;
	total_len = 0;
	while (argv[++j])
	{
		if (j <= i)
			len += ft_strlen(argv[j]);
		total_len += ft_strlen(argv[j]);
	}
	j = total_len - len;
	ft_memmove(config->history[config->hindex - 1],
		config->history[config->hindex - 1] + len + 2, j);
	config->history[config->hindex - 1][j] = 0;
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
		else if (argv[i][j] == 's' && argv[i + 1])
			ft_stock_cmd(config, argv, i);
		else if (argv[i][j] == 'a')
			ft_purge_hist_opt(config, config->history, config->hindex_first, 0);
		else if (argv[i][j] == 'w')
			ft_purge_hist_opt(config, config->history, config->hindex_first, 2);
		else if (ft_error("fc", "event not found", argv[i], CR_ERROR))
			return ;
	}
}
