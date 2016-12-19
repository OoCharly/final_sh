/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 13:40:06 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/19 16:49:41 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		ft_get_cur_col(char *cmd, size_t end, t_stream *stream)
{
	size_t	pos;
	size_t	col;
	int		j;

	col = stream->col;
	pos = stream->config->prompt_len % stream->col;
	j = -1;
	while (cmd[++j] && j <= (int)end)
	{
		if (cmd[j] == '\t')
			pos = (pos + 4 < col) ? pos + 4 : 0 + ((pos + 4) % col);
		else if (cmd[j] == '\n')
			pos = 0;
		else
			pos = (pos && !(pos % col)) ? 0 : pos + 1;
	}
	return (pos);
}
