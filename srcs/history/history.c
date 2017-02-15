/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:16 by tboos             #+#    #+#             */
/*   Updated: 2017/02/15 16:48:38 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_decr_history(t_config *config, int *hindex)
{
	if (*hindex > 0)
		(*hindex)--;
	else
		*hindex = HISTORY_SIZE - 1;
	if (config)
	{
		if (*hindex == config->hindex_first)
			ft_decr_history(NULL, &config->hindex_first);
		if (config->history_new_size)
			config->history_new_size--;
	}
}

void	ft_incr_history(t_config *config, int *hindex)
{

	if (*hindex < HISTORY_SIZE - 1)
		(*hindex)++;
	else
		*hindex = 0;
	if (config)
	{
		if (*hindex == config->hindex_first)
			ft_incr_history(NULL, &config->hindex_first);
		if (config->history_new_size < HISTORY_SIZE)
			config->history_new_size++;
	}
}

/*
**Appends current command to config->history. When mode is eguals to zero,
**config->ncmd_index is filled to.
*/

int		ft_is_memerizable(char *cmd)
{
	while (cmd && *cmd)
	{
		if (ft_isprint(*cmd) && !ft_isspace(*cmd))
			return (1);
		++cmd;
	}
	return (0);
}

void	ft_push_history(t_stream *stream, t_config *config)
{
	stream->shindex = config->hindex;
	ft_freegiveone((void **)&(config->history[config->hindex]));
	if (stream->command && stream->command[0])
	{
		if (!(config->history[config->hindex] = ft_strdup(stream->command)))
			stream->state = -2;
	}
}
