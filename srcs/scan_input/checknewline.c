/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checknewline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:59:34 by rbaran            #+#    #+#             */
/*   Updated: 2016/11/27 12:32:56 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_checknewline(t_stream *stream, size_t p)
{
	size_t	pos;
	size_t	i;

	pos = stream->config->prompt_len % stream->col;
	i = -1;
	while (++i < p)
		if (stream->command[i] == '\n' || ++pos == stream->col)
			pos = 0;
	if (stream->command[i] == '\n' || pos == stream->col - 1)
		return ((int)pos);
	else
		return (-1);
}
