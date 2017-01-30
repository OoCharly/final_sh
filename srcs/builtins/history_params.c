/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:20:47 by maxpetit          #+#    #+#             */
/*   Updated: 2017/01/30 13:05:33 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_line_file(t_config *config)
{
	int		i;
	int		fd;
	char	*line;
	char	*file;

	i = 0;
	file = (config->hlocbis) ? config->hlocbis : config->hloc;
	if (((fd = open(file, O_RDONLY)) < 0)
		&& ft_error(SHNAME, NULL, "open error", CR_ERROR))
		return (-1);
	while (get_next_line(fd, &line) && ++i)
		ft_freegiveone((void **)&(line));
	ft_freegiveone((void **)&(line));
	close(fd);
	return (i);
}

static void	ft_delete_history_index(t_config *config, int idx)
{
	int len;

	len = (HISTORY_SIZE - idx) * sizeof(void *);
	ft_freegiveone((void **)config->history + idx);
	ft_memmove(config->history + idx, config->history + idx + 1, len);
	ft_decr_history(&(config->hindex));
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

static void	ft_purge_history_during_run(t_config *config)
{
	ft_purge_history(config, config->hist_newcmd, config->ncmd_index, 0);
	ft_strtabfree_content(config->hist_newcmd);
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
		else if (argv[i][j] == 'a')
			ft_purge_history_during_run(config);
		else if (argv[i][j] == 'w')
			ft_purge_history(config, config->hist_newcmd, HISTORY_SIZE, 2);
		else if (argv[i][j] == 's' && argv[i + 1])
				ft_stock_cmd(config, argv, i);
		else if (ft_error("fc", "event not found", argv[i], CR_ERROR))
			return ;
	}
}
