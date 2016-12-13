/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprompt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 16:23:59 by rbaran            #+#    #+#             */
/*   Updated: 2016/12/13 14:58:17 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_flushsearch(t_stream *stream)
{
	size_t		size;
	int			index;

	if (stream->command && stream->command[0])
	{
		if ((index = ft_strstri(stream->command, stream->search)) != -1)
		{
			size = ft_strlen(stream->search);
			write(SFD, stream->command, index);
			ft_putstr_fd("\033[4m", SFD);
			ft_putstr_fd(stream->search, SFD);
			ft_putstr_fd("\033[00m", SFD);
			ft_putstr_fd(stream->command + index + size, SFD);
		}
		else
			ft_putstr_fd(stream->command, SFD);
		stream->pos = ft_strlen(stream->command);
	}
}

void	ft_sprompt(t_stream *stream)
{
	char	*buf;
	char	*kill;
	//int		index;

	if (stream->search && stream->search[0] &&
		(buf = ft_strjoin("back-i-search: ", stream->search)))
	{
		kill = buf;
		buf = ft_strjoin(buf, "_");
		ft_freegiveone((void**)&kill);
	}
	else
		buf = ft_strdup("back-i-search: _");
	ft_underline_mess(buf, stream);
	ft_freegiveone((void**)&buf);
	/*if (stream->command && stream->search && stream->search[0]
			&& (index = ft_strstri(stream->command, stream->search)) != -1)
		ft_gomatch(stream, (size_t)index);*/
}
