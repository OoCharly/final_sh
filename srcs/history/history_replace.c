/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:06:06 by maxpetit          #+#    #+#             */
/*   Updated: 2017/02/17 13:07:08 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_ret_idx(char *str, int i, char **su)
{
	int		idx;
	int		j;
	char	*idx_str;
	int		ret;

	j = 0;
	idx = ++i;
	if (str[i] && (!ft_isdigit(str[i]) || str[i] == '0'))
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
				return ((j > 0) ? ft_strdup(config->history[j - 1]) : NULL);
			}
			if (str[i + 1] && ((j = ft_ret_idx(str, i, su)) >= 0))
			{
				ft_decr_history(NULL, &j);
				return (ft_strdup(config->history[j]));
			}
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
	ret_hist = NULL;
	idx_hist = ft_loop_hist(str, &pre, &su);
	if (!idx_hist && ft_freegiveone((void**)&pre)
			&& ft_freegiveone((void**)&idx_hist))
		return (NULL);
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
