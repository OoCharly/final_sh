/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 16:21:00 by tboos             #+#    #+#             */
/*   Updated: 2017/01/08 16:21:02 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strchr_dodge(char *str, char c)
{
	while (str && *str)
	{
		if (*str == c)
			return (str);
		if (*str == '\'' || *str == '\"')
			if (ft_gonextquote(&str, *str))
				return (NULL);
		if (*str == '\\')
			++str;
		if (*str)
			++str;
	}
	return (NULL);
}

static char	*ft_checkpaste(t_stream *stream)
{
	char	*match;
	char	*err;

	match = stream->command;
	while ((stream->command)
		&& (match = ft_strchr_dodge(match, '\n')))
	{
		err = stream->command;
		*match = 0;
		if (!ft_matchchr(&err))
		{
			stream->config->exclamation = match ? ft_strdup(match + 1)
				: stream->config->exclamation;
			return (NULL);
		}
		*match = '\n';
		++match;
	}
	match = stream->command;
	return (ft_matchchr(&match));
}

char		*ft_pastereturn(t_stream *stream)
{
	char	*err;
	size_t	pos;

	err = NULL;
	if (ft_history_exclamation(stream))
		ft_winsize();
	pos = stream->pos;
	ft_gohome(stream);
	if (!(err = ft_checkpaste(stream)))
	{
		ft_winsize();
		ft_goend(stream);
		return (NULL);
	}
	else
		ft_gomatch(stream, pos);
	return (err);
}
