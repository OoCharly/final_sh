/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:16 by tboos             #+#    #+#             */
/*   Updated: 2016/12/08 10:07:08 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_decr_history(int *hindex)
{
	if (*hindex > 0)
		(*hindex)--;
	else
		*hindex = HISTORY_SIZE;
}

void	ft_incr_history(int *hindex)
{
	if (*hindex < HISTORY_SIZE)
		(*hindex)++;
	else
		*hindex = 0;
}

/*
**Appends current command to config->history.
*/

void	ft_push_history(t_stream *stream, t_config *config)
{
	stream->shindex = config->hindex;
	ft_freegiveone((void **)&(config->history[config->hindex]));
	if (stream->command && stream->command[0])
		if (!(config->history[config->hindex] = ft_strdup(stream->command)))
			stream->state = -2;
}
