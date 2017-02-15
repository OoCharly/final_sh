/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:01:50 by maxpetit          #+#    #+#             */
/*   Updated: 2017/02/15 19:13:36 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_count_line_file(t_config *config)
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

static int	ft_printhist(t_config *config, int n)
{
	int		i;
	int		num;
	char	*len;
	char	*index;

	i = -1;
	num = 1;
	len = ft_itoa(HISTORY_SIZE);
	if (!config->history[0])
		i++;
	while (config->history[++i] && i < n)
	{
		index = ft_itoa(num);
		ft_putstrpad(index, ft_strlen(len) + 1, 'L');
		ft_putendl(config->history[i]);
		ft_strdel(&index);
		num++;
	}
	ft_strdel(&len);
	return (1);
}

/*
**Checks if an argv is something else than an argument which begin by '-'. If
**an argument does not begin by '-', then this argument is a name of file and
**ft_get_afterarg changes the path of config->hloc for the path of argv[i].
*/

static int	ft_get_afterarg(t_config *config, char **argv, int i)
{
	int		j;
	char	c;
	char	*file;

	while (argv[i] && argv[i][0] == '-')
	{
		if (ft_strchr(argv[i], 's'))
			return (1);
		i++;
	}
	if (argv[i] && !ft_strisdigit(argv[i]))
	{
		file = ft_strrchr(config->hloc, '/');
		j = file - config->hloc;
		c = config->hloc[j];
		config->hloc[j] = 0;
		config->hlocbis = ft_strslashjoin(config->hloc, argv[i]);
		config->hloc[j] = c;
	}
	return (1);
}

/*
**If there are no arguments after history or if this argument is a number,
**launch ft_printhist function. Otherwise applies corresponding function to
**the argument if this one exists.
*/

void		ft_history(char **argv, t_config *config)
{
	int i;
	int n;

	i = 0;
	if ((!argv[1] || ft_strisdigit(argv[1]))
		&& (n = (!argv[1]) ? HISTORY_SIZE : ft_atoi(argv[1])))
		ft_printhist(config, n);
	while (argv[++i] && !ft_strisdigit(argv[i]))
		if (argv[i][0] == '-' && ft_get_afterarg(config, argv, i))
			ft_manage_param(argv, i, config);
	ft_freegiveone((void**)&(config->hlocbis));
}
