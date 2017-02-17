/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 16:38:05 by maxpetit          #+#    #+#             */
/*   Updated: 2017/02/17 13:07:43 by maxpetit         ###   ########.fr       */
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
			if (ret[1] == 0)
				return (0);
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
	int			flag;
	int			i;

	flag = 0;
	i = 0;
	if ((i = ft_st_checkchars(stream->command + i, "!")))
	{
		if (stream->command[i] && (stream->command[i] == '!'
			|| (ft_isdigit(stream->command[i])
			&& ft_atoi(stream->command + i) <= HISTORY_SIZE)))
		{
			if ((tmp = ft_create_strhistidx(stream->command))
				&& (flag = 1))
			{
				ft_freegiveone((void**)&(stream->command));
				stream->command = tmp;
			}
		}
	}
	if (flag)
		return (1);
	return (0);
}

int			ft_history_rep(t_stream *stream)
{
	char		*tmp;
	int			flag;
	int			i;

	flag = 0;
	i = 0;
	if ((i = ft_st_checkchars(COMP_BEGIN + i, "!")))
	{
		if (COMP_BEGIN[i] && (COMP_BEGIN[i] == '!'
			|| (ft_isdigit(COMP_BEGIN[i])
			&& ft_atoi(COMP_BEGIN + i) <= HISTORY_SIZE)))
		{
			if ((tmp = ft_create_strhistidx(COMP_BEGIN))
				&& (flag = 1))
			{
				ft_freegiveone((void**)&(COMP_BEGIN));
				COMP_BEGIN = tmp;
			}
		}
	}
	if (flag)
		return (1);
	return (0);
}
