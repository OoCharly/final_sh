/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 14:30:52 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:28:04 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			ft_free_line(t_line **begin, t_line *next)
{
	while ((*begin)->next != next)
		*begin = (*begin)->next;
	if ((*begin)->next == *begin)
	{
		free(*begin);
		*begin = NULL;
	}
	else
	{
		(*begin)->next = next->next;
		free(next);
	}
	return (1);
}

static int			ft_findread(t_line **begin, t_line *next, int fd, int mode)
{
	char			tmp[BUFF_SIZE + 1];
	int				ret;

	while (*begin && (*begin)->fd != fd && (*begin)->next != next)
		*begin = (*begin)->next;
	if (mode == FIND && *begin && (*begin)->fd == fd)
		return (1);
	if (!(ret = read(fd, tmp, BUFF_SIZE)))
		return (0);
	tmp[ret] = '\0';
	if (mode == READ && ft_strcpy((*begin)->data, tmp))
		return (ret);
	if (*begin && (*begin)->fd != fd && !((*begin)->next = MALLOC))
		return (-1);
	else if (!(*begin) && !(*begin = MALLOC))
		return (-1);
	if (next)
		*begin = (*begin)->next;
	ft_memcpy((*begin)->data, tmp, BUFF_SIZE);
	(*begin)->ret = ret;
	(*begin)->fd = fd;
	(*begin)->next = (next ? next : *begin);
	return (1);
}

static int			ft_strcut(char *src, int c, int ret)
{
	char	*tmp;

	tmp = src;
	while (ret--)
	{
		if (*tmp == c || *tmp == '\0')
		{
			*tmp = '\0';
			return (tmp - src + 1);
		}
		tmp++;
	}
	*tmp = '\0';
	return (0);
}

static int			ft_gnl_reset(t_line **begin)
{
	while (*begin)
		ft_free_line(begin, (*begin)->next);
	return (-1);
}

int					get_next_line(int const fd, char **line)
{
	static t_line	*begin = NULL;
	int				test;
	char			*tmp;

	test = -1;
	if (fd < 0 || !line || read(fd, NULL, 0) < 0
		|| (test = ft_findread(&begin, begin, fd, FIND)) <= 0)
		return ((fd < 0 ? ft_gnl_reset(&begin) : test));
	*line = ft_memalloc(1);
	while (!(test = ft_strcut(DATA, '\n', RET))
		&& (tmp = *line)
		&& (*line = ft_strjoin(*line, DATA))
		&& (RET = ft_findread(&begin, begin, fd, READ))
		&& ft_freegiveone((void **)&tmp))
		if (!(*line))
			return (-1);
	if (RET && test)
	{
		tmp = *line;
		*line = ft_strjoin(*line, DATA);
		free(tmp);
		RET = RET - test;
		ft_strncpy(DATA, DATA + test, RET);
	}
	return ((RET ? 1 : ft_free_line(&begin, begin)));
}
