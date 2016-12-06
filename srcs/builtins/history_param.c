/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 15:08:47 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/05 19:33:40 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **ft_realloc_tab(char **tmp, int *len)
{
	int		i;
	char	**new_tab;

	i = -1;
	*len *= *len;
	new_tab = (char **)ft_memalloc(sizeof(void *) * (*len + 1));
	while (tmp[++i])
		new_tab[i] = ft_strdup(tmp[i]);
	return (new_tab);
}

static void	ft_fillhist(t_config *config, char **tmp_hist, int i)
{
	int j;

	j = 0;
	printf("_hindex_%d_\n", config->hindex);
	printf("_i_%d_\n", i);
	if (config->hindex >= HISTORY_SIZE)
		ft_error(SHNAME, NULL, "Full history", CR_ERROR);
	else if (i <= HISTORY_SIZE)
		while (config->hindex < HISTORY_SIZE && i--)
			config->history[config->hindex++] = tmp_hist[j++];
	else if (i > HISTORY_SIZE)
	{
		j = i - (HISTORY_SIZE - config->hindex);
		while (config->hindex < HISTORY_SIZE)
			config->history[config->hindex++] = tmp_hist[j++];
	}
}

static void	ft_filltmphist(char *line, char **tmp, int i)
{
	static int	len_malloc;
	char		**kill;

	len_malloc = (!len_malloc) ? HISTORY_SIZE + 1 : len_malloc;
	if (i < len_malloc)
		tmp[i] = (line[0] == '|') ? ft_memmove(line, line + 1, ft_strlen(line + 1) + 1) : line;
	else
	{
		kill = tmp;
		tmp = ft_realloc_tab(tmp, &len_malloc);
		tmp[i] = (line[0] == '|') ? ft_memmove(line, line + 1, ft_strlen(line + 1) + 1) : line;
		free(kill);
		kill = NULL;
	}
}

void		ft_readfile(t_config *config)
{
	int		fd;
	int		i;
	char	*line;
	char	**tmp;

	i = 0;
	line = NULL;
	if (((fd = open("history.bck", O_RDONLY)) == -1) 
		&& ft_error(SHNAME, NULL, "Open error in history builtin.", CR_ERROR))
		return ;
	if (!(tmp = (char **)ft_memalloc(sizeof(void *) * (HISTORY_SIZE + 1)))
		&& ft_error(SHNAME, NULL, "Malloc error in history builtin.", CR_ERROR))
		return ;
	while (get_next_line(fd, &line) && ++i)
		ft_filltmphist(line, tmp, i - 1);
	if (i)
		ft_fillhist(config, tmp, i);
	free(tmp);
	close(fd);
}
