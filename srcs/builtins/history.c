/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:01:50 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/08 10:03:21 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_padding(char orientation, char *str, size_t size, char elem)
{
	size_t	i;
	char	*new;

	if ((size_t)ft_strlen(str) != size)
	{
		i = (orientation == 'L') ? 0 : (size_t)ft_strlen(str);
		new = ft_strnew((int)size);
		if (orientation == 'R')
			new = ft_strcpy(new, str);
		while ((size_t)ft_strlen(str) != size)
		{
			new[i] = elem;
			i++;
			size--;
		}
		if (orientation == 'L')
			new = ft_strcat(new, str);
		return (new);
	}
	return (str);
}

static int ft_check_num(char *argv)
{
	int i;

	i = -1;
	while (argv[++i])
		if (!ft_isdigit(argv[i]))
			return (0);
	return (1);
}

static int ft_printhist(char **history, int n)
{
	int		i;
	char	*len;
	char	*index;
	char	*pad;

	i = -1;
	len = ft_itoa(HISTORY_SIZE);
	if (!history)
		return (0);
	while (history[++i] && i < n)
	{
		index = ft_itoa(i + 1);
		pad = ft_padding('R', index , ft_strlen(len) + 1, ' ');
		ft_putstr(pad);
		ft_putendl(history[i]);
		ft_strdel(&index);
		ft_strdel(&pad);
	}
	ft_strdel(&len);
	return (1);
}

static void ft_manage_param(char **argv, int i, t_config *config)
{
	int j;
	int idx;
	int len;

	j = 0;
	while (argv[i][++j] && !ft_check_num(argv[i]))
	{
		if (argv[i][j] == 'c' && config->history[0] && !(config->hindex = 0))
			ft_strtabfree_content(config->history);
		else if (argv[i][j] == 'd' && argv[i + 1] && ft_check_num(argv[i + 1])
			&& ((idx = ft_atoi(argv[i + 1]) - 1) >= 0) && idx < HISTORY_SIZE)
		{
			len = (HISTORY_SIZE - idx) * sizeof(void *);
			ft_memmove(config->history + idx, config->history + idx + 1, len);
			ft_decr_history(&(config->hindex));
		}
		else if (argv[i][j] == 'r')
			ft_load_history(config);
		else if (ft_error("fc", "event not found", argv[i], CR_ERROR))
			return ;
	//	else if (*argv == 'w')
	//		ft_write_histfile(config);
	}
}

/*
**If there are no arguments after history or if this argument is a number,
**launch ft_printhist function. Otherwise apply corresponding function to
**the argument if this one exists.
*/

void ft_history(char **argv, t_config *config)
{
	int i;
	int n;

	i = 0;
	printf("_hindex1_%d_\n", config->hindex);
	if ((!argv[1] || ft_check_num(argv[1]))
		&& (n = (!argv[1]) ? HISTORY_SIZE : ft_atoi(argv[1])))
		ft_printhist(config->history, n);
	while (argv[++i] && !ft_check_num(argv[i]))
	{
		if (argv[i][0] == '-')
			ft_manage_param(argv, i,config);
		else if (ft_error("fc", "event not found", argv[i], CR_ERROR))
			return ;
	}
}
