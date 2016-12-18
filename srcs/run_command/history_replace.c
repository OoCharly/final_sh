/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:06:06 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/18 16:42:37 by maxpetit         ###   ########.fr       */
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
	ft_ret_intervalquote(str, &begin, &end, i);
	if ((ret = ft_strchr(str + i, '!')))
	{
		i = ret - str;
		if ((end == 0 || (i < begin))
			&& ((ft_strcmp(ret, str + i) && *(ret - 1) != '\\')
			|| (!ft_strcmp(ret, str + i))))
			return (1);
		i = end;
		return (ft_checkhist(str));
	}
	return (0);
}

static int	ft_ret_idx(char *str, int i, char **su)
{
	int		idx;
	int		j;
	char	*idx_str;
	int		ret;

	j = 0;
	idx = ++i;
	if (str[i] && !ft_isdigit(str[i]))
		return (-1);
	while (str[i] && ft_isdigit(str[i++]))
		j++;
	if (!(idx_str = ft_strnew(j))
		&& ft_error(SHNAME, NULL, "malloc error", CR_ERROR))
		return (-1);
	j = -1;
	while (str[idx] && ft_isdigit(str[idx]))
		idx_str[++j] = str[idx++];
	if (str[idx])
		*su = str + idx;
	ret = ft_atoi(idx_str);
	ft_freegiveone((void**)&idx_str);
	return (ret);
}

/*
**Returns the index which is after the charactere '!', if no '!' are found or
**if only '!' precedated by '\' are found return -1.
*/

static char	*ft_loop_hist(char *str, char **pre, char **su)
{
	int			i;
	int			j;
	t_config	*config;

	i = -1;
	while ((config = ft_save_config(NULL)) && str[++i])
		if (str[i] == '!' && (i == 0 || str[i - 1] != '\\'))
		{
			if (!(*pre = ft_strnew(i + 2))
				&& ft_error(SHNAME, NULL, "malloc error", CR_ERROR))
				return (NULL);
			if (ft_strncpy(*pre, str, i) && str[i + 1] && str[i + 1] == '!')
			{
				if (str[i + 2])
					*su = str + i + 2;
				j = config->hindex;
				ft_decr_history(&j);
				return ((j > 0) ? ft_strdup(config->history[j - 1]) : NULL);
			}
			if (str[i + 1] && ((j = ft_ret_idx(str, i, su)) >= 0))
				return (ft_strdup(config->history[j - 1]));
			else if (ft_error(SHNAME, NULL, "syntax error", CR_ERROR))
				return (NULL);
		}
	return (NULL);
}

char		*ft_create_strhistidx(char *str)
{
	int		i;
	char	*pre;
	char	*su;
	char	*idx_hist;
	char	*ret_hist;

	pre = NULL;
	su = NULL;
	idx_hist = ft_loop_hist(str, &pre, &su);
	if (idx_hist)
	{
		i = ft_strlen(pre) + ft_strlen(idx_hist) + ft_strlen(su);
		ret_hist = ft_strnew(++i);
		if (pre)
			ft_strcat(ret_hist, pre);
		ft_strcat(ret_hist, idx_hist);
		if (su)
			ft_strcat(ret_hist, su);
		ft_freegiveone((void**)&pre);
		ft_freegiveone((void**)&idx_hist);
		ret_hist[i] = 0;
		return (ret_hist);
	}
	return (NULL);
}
