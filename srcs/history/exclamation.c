/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 16:38:05 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/22 15:20:31 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_ret_intervalquote(char *str, int *begin, int *end, int i)
{
	char	*ret;

	if ((ret = ft_strchr(str + i, '\'')))
	{
		*begin = ret - str;
		*end = ft_dodge_quote(str, *begin);
		return (1);
	}
	return (0);
}

/*
**Checks if there is the character '!' in str without a '\' ahead.
*/

int			ft_checkhist(char *str)
{
	static int	i;
	int			begin;
	int			end;
	char		*ret;

	begin = 0;
	end = 0;
	if (str[i])
	{
		ft_ret_intervalquote(str, &begin, &end, i);
		if ((ret = ft_strchr(str + i, '!')))
		{
			i = ret - str;
			if ((end == 0 || (i < begin))
				&& ((ft_strcmp(ret, str + i) && *(ret - 1) != '\\')
				|| (!ft_strcmp(ret, str + i))) && !(i = 0))
				return (1);
			i = end;
			return (ft_checkhist(str));
		}
	}
	i = 0;
	return (0);
}

int			ft_history_exclamation(t_stream *stream)
{
	char		*tmp;
	char		*mem;
	t_config	*config;

	if (ft_checkhist(stream->command))
	{
		mem = NULL;
		config = ft_save_config(NULL);
		ft_incr_history(&config->hindex);
		tmp = stream->command;
		while ((tmp = ft_create_strhistidx(tmp))
			&& ft_freegiveone((void**)&mem))
			mem = tmp;
		ft_freegiveone((void**)&(stream->command));
		stream->command = mem;
		return (1);
	}
	return (0);
}
