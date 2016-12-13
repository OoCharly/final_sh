/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:01:50 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/09 19:29:35 by maxpetit         ###   ########.fr       */
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
**If the new path of config->hloc is biggest than the first, then the new has
**to be realloced.
*/

static void	ft_realloc_tmphloc(t_config *config, char *file, int l_h, int l_f)
{
	char *hloc;
	char c;

	hloc = ft_return_hloc(NULL, 0);
	c = hloc[l_h - l_f];
	hloc[l_h - l_f] = 0;
	config->hloc = ft_strslashjoin(hloc, file);
	hloc[l_h - l_f] = c;
}

/*
**Checks if an argv is something else than an argument which begin by '-'. If
**an argument does not begin by '-', then this argument is a name of file and
**ft_get_afterarg changes the path of config->hloc for the path of argv[i].
*/

static int	ft_get_afterarg(t_config *config, char **argv, int i)
{
	int		len_arg;
	int		len_file;
	int		len;
	char	*file;

	len = ft_strlen(config->hloc);
	while (argv[i] && argv[i][0] == '-')
		i++;
	if (argv[i] && (file = ft_strrchr(config->hloc, '/'))
		&& (len_arg = ft_strlen(argv[i]))
		&& (len_file = ft_strlen(file)))
	{
		if (len_arg <= len_file)
		{
			ft_bzero(config->hloc + (len - len_file) + 1, len_file);
			ft_memmove(config->hloc + (len - len_file) + 1, argv[i], len_arg);
		}
		else if (ft_freegiveone((void **)&(config->hloc)))
			ft_realloc_tmphloc(config, argv[i], len, len_file);
	}
	return (1);
}

/*
**Records the first path of config->hloc, like registered in function
**ft_history_loc_init. At the end of the programe, mode eguals to one and static
**variable mem is freed. Otherwise when mode is eguals to zero, the inital value
**of mem is returned.
*/

char		*ft_return_hloc(char *hloc, int mode)
{
	static char *mem;

	if (mode)
		mem = ft_strdup(hloc);
	if (mode == -1)
		ft_freegiveone((void **)&hloc);
	return (mem);
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
