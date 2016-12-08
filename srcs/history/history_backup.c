/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_backup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:59:12 by tboos             #+#    #+#             */
/*   Updated: 2016/12/08 10:21:13 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Appends commands registered in history.bck file in config->history. For any 
**new command a pipe is wrote ahead.
*/

static int	ft_safeputstr(int fd, char *str)
{
	if (str && (0 > write(fd, "|", 1) || 0 > write(fd, str, ft_strlen(str))))
	{
		ft_error(SHNAME, NULL, SAVE_H_ERR, CR_ERROR | SERROR);
		ft_freegiveone((void **)&str);
		return (0);
	}
	ft_freegiveone((void **)&str);
	return (1);
}

/*
**Opens hystory file. Makes a loop wich begin at config->hindex, and for any 
**command calls ft_safeputstr.
*/

void		ft_purge_history(t_config *config)
{
	int		i;
	int		fd;

	if ((fd = open(config->hloc, O_CREAT | O_WRONLY
			| O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		ft_error(SHNAME, NULL, SAVE_H_ERR, CR_ERROR | SERROR);
	else
	{
		i = config->hindex;
		while (1)
		{
			ft_incr_history(&i);
			if (!ft_safeputstr(fd, config->history[i])
				|| i == config->hindex)
				break ;
			if (config->history[i])
				write(fd, "\n", 1);
		}
		write(fd, "\0", 1);
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
			ft_incr_history(&(config->hindex));
		ft_freegiveone((void **)&(config->history[config->hindex]));
		config->history[config->hindex] = (char*)ft_memmove(tmp, tmp + 1
			, ft_strlen(tmp));
	}
	else if (config->history[config->hindex])
	{
		kill = config->history[config->hindex];
		config->history[config->hindex] = ft_strjoin(kill, "\n");
		ft_freegiveone((void**)&kill);
		kill = config->history[config->hindex];
		config->history[config->hindex] = ft_strjoin(kill, tmp);
		ft_freegiveone((void**)&kill);
		ft_freegiveone((void**)&tmp);
	}
}

/*
**Opens history.bck and fills config->history with file contents.
*/

void		ft_load_history(t_config *config)
{
	int		fd;
	char	*tmp;

	if ((fd = open(config->hloc, O_RDONLY)) < 0)
		return ;
	else
	{
		while (get_next_line(fd, &tmp) > 0)
			ft_fill_history(config, tmp);
		get_next_line(-1, NULL);
		close(fd);
	}
}
