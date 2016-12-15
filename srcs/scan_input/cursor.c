/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:40:06 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/14 13:41:40 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		ft_get_cur_col(char *cmd, size_t end, t_stream *stream)
{
	size_t	pos;
	int		j;

	pos = stream->config->prompt_len % stream->col;
	j = -1;
	while (cmd[++j] && j <= (int)end)
	{
		if (cmd[j] == '\t')
			pos = (pos + 4 < stream->col) ? pos + 4 : 0 + ((pos + 4) % stream->col);
		else if (cmd[j] == '\n')
			pos = 0;
		else
			pos = (pos && !(pos % stream->col)) ? 0 : pos + 1;
	}
	return (pos);
}
