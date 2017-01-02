/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checknewline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 13:59:34 by rbaran            #+#    #+#             */
/*   Updated: 2017/01/02 17:05:46 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_checknewline(t_stream *stream, size_t p)
{
	size_t	pos;
	size_t	i;

	pos = stream->config->prompt_len % stream->col;
	if (!stream->command)
		return ((int)pos);
	i = -1;
	while (++i < p && stream->command[i])
		if (stream->command[i] == '\n' || ++pos == stream->col)
			pos = 0;
	return (pos);
}
