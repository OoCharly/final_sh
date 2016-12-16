/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:01:50 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/15 16:47:47 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_printhist(char **history, int n)
{
	int		i;
	char	*len;
	char	*index;

	i = -1;
	len = ft_itoa(HISTORY_SIZE);
	if (!history)
		return (0);
	while (history[++i] && i < n)
	{
		index = ft_itoa(i + 1);
		ft_putstrpad(index, ft_strlen(len) + 1, 'L');
		ft_putendl(history[i]);
		ft_strdel(&index);
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
		i++;
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
		ft_printhist(config->history, n);
	while (argv[++i] && !ft_strisdigit(argv[i]))
		if (argv[i][0] == '-' && ft_get_afterarg(config, argv, i))
			ft_manage_param(argv, i, config);
}
