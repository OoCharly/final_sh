/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_backup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:59:12 by tboos             #+#    #+#             */
/*   Updated: 2017/02/15 19:15:00 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Adds commands registed in config->history in history file. For any
**new command a pipe is wrote ahead.
*/

static int	ft_safeputstr(int fd, char *str, int mode, int *i)
{
	if (str && (0 > write(fd, "|", 1) || 0 > write(fd, str, ft_strlen(str))))
	{
		ft_error(SHNAME, NULL, SAVE_H_ERR, CR_ERROR | SERROR);
		ft_incr_history(NULL, i);
		if (mode == 1)
			ft_freegiveone((void **)&str);
		return (0);
	}
	if (str)
		write(fd, "\n", 1);
	if (mode == 1)
		ft_freegiveone((void **)&str);
	ft_incr_history(NULL, i);
	return (1);
}

void		ft_purge_hist_opt(t_config *config, char **hist, int index, int mde)
{
	int		i;
	int		j;
	int		fd;
	char	*file;

	j = 0;
	file = (config->hlocbis) ? config->hlocbis : config->hloc;
	if (mde && (fd = open(file, O_CREAT | O_WRONLY
		| O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		ft_error(SHNAME, NULL, SAVE_H_ERR, CR_ERROR | SERROR);
	else if (!mde && (fd = open(file, O_CREAT | O_WRONLY
		| O_APPEND, S_IRUSR | S_IWUSR)) < 0)
		ft_error(SHNAME, NULL, SAVE_H_ERR, CR_ERROR | SERROR);
	else
	{
		i = index;
		while (j < config->history_new_size)
		{
			if (!ft_safeputstr(fd, hist[i], mde, &i)
				|| i == index)
				break ;
			j++;
		}
		close(fd);
	}
}

/*
**Opens hystory file. Makes a loop wich begin at config->hindex, and for any
**command calls ft_safeputstr.
*/

void		ft_purge_history(t_config *config, char **hist, int index, int mode)
{
	int		i;
	int		fd;
	char	*file;

	file = (config->hlocbis) ? config->hlocbis : config->hloc;
	if (mode && (fd = open(file, O_CREAT | O_WRONLY
		| O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		ft_error(SHNAME, NULL, SAVE_H_ERR, CR_ERROR | SERROR);
	else if (!mode && (fd = open(file, O_CREAT | O_WRONLY
		| O_APPEND, S_IRUSR | S_IWUSR)) < 0)
		ft_error(SHNAME, NULL, SAVE_H_ERR, CR_ERROR | SERROR);
	else
	{
		i = index;
		while (1)
		{
			if (!ft_safeputstr(fd, hist[i], mode, &i)
				|| i == index)
				break ;
		}
		close(fd);
	}
}

static void	ft_fill_history(t_config *config, char *tmp)
{
	char	*kill;

	if (tmp[0] == '|')
	{
		if (config->history[config->hindex]
			&& config->history[config->hindex][0])
			ft_incr_history(NULL, &(config->hindex));
		ft_freegiveone((void **)&(config->history[config->hindex]));
		config->history[config->hindex] = ft_strdup(tmp + 1);
		ft_freegiveone((void**)&tmp);
	}
	else if (config->history[config->hindex])
	{
		kill = config->history[config->hindex];
		config->history[config->hindex] = ft_strchrjoin(kill, '\n', tmp);
		ft_freegiveone((void**)&kill);
		ft_freegiveone((void**)&tmp);
	}
	else
		ft_freegiveone((void**)&tmp);
}

/*
**Opens the file where history data are registed file and fills config->history
**with file contents.
*/

void		ft_load_history(t_config *config)
{
	int		fd;
	int		i;
	char	*tmp;
	char	*file;

	i = -1;
	file = (config->hlocbis) ? config->hlocbis : config->hloc;
	if ((fd = open(file, O_RDONLY)) < 0)
		return ;
	else
	{
		while ((++i < HISTORY_SIZE - 1) && (get_next_line(fd, &tmp) > 0))
			ft_fill_history(config, tmp);
		config->hindex_first = i;
		ft_incr_history(NULL, &(config->hindex));
		get_next_line(-1, NULL);
		close(fd);
	}
}
