/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:57:39 by jmunoz            #+#    #+#             */
/*   Updated: 2017/02/17 19:12:52 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_addtoline(t_stream *stream, char *add, char *b)
{
	size_t	size;
	size_t	pos;
	char	*tmp;

	if (add)
	{
		tmp = add;
		pos = stream->pos;
		ft_gomatch(stream, b - stream->command);
		ft_memmove(b, stream->command + pos,
		ft_strlen(stream->command + pos) + 1);
		ft_bzero(stream->buf, 256);
		while ((size = ft_strlen(ft_strncpy(stream->buf, add, 255))) == 255)
		{
			ft_append(stream);
			add = add + size;
			ft_bzero(stream->buf, 256);
		}
		ft_append(stream);
		ft_freegiveone((void**)&tmp);
	}
	ft_bzero(stream->buf, 256);
}

int				ft_rep(t_stream *stream, char *b)
{
	char	**arg;
	int		j;
	int		ret;
	char	*add;

	signal(SIGINT, SIG_IGN);
	b = (void*)b;
	j = 0;
	ret = 0;
	arg = NULL;
	ret = ft_history_rep(stream);
	arg = ft_strtabadd(arg, COMP_BEGIN);
	while (j < 4)
		ret += ft_check_insert(&arg, j++, stream->config);
	if (!ret && ft_freegiveone((void**)&arg))
		return (0);
	else
		COMP_BEGIN = NULL;
	if ((add = ft_strtabchrjoin(arg, ' ')))
		add[ft_strlen(add) - 1] = 0;
	ft_addtoline(stream, add, b);
	ft_strtabfree(arg);
	arg = NULL;
	signal(SIGINT, &ft_signal_handle);
	return (1);
}
