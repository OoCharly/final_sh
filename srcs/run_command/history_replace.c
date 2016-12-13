/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:06:06 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/13 20:09:13 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Checks if there are one of the following globbing pathern in str : !
*/

int			ft_checkhist(char *str)
{
	char *ret;

	if ((ret = ft_strchr(str, '!')))
		if ((ft_strcmp(ret, str) && *(ret - 1) != '\\')
			|| (!ft_strcmp(ret, str)))
			return (1);
	return (0);
}

static int	ft_ret_idx(char *str, int i, char **pre, char **su)
{
	int		idx;
	int		j;
	char	*idx_str;
	int		ret;
	char	c;

	j = 0;
	c = str[i];
	str[i] = 0;
	*pre = ft_strdup(str);
	str[i] = c;
	idx = ++i;
	while (str[i] && ft_isdigit(str[i++]))
		j++;
	idx_str = ft_strnew(j);
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

static int	ft_loop_hist(char *str, char **pre, char **su)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '!' && (i == 0 || str[i - 1] != '\\'))
			return (ft_ret_idx(str, i, pre, su));
	return (-1);
}

char		*ft_create_strhistidx(t_config *config, char *str)
{
	int		i;
	char	*pre;
	char	*su;
	char	*idx_hist;
	char	*ret_hist;

	pre = NULL;
	su = NULL;
	i = ft_loop_hist(str, &pre, &su);
	if (i != -1)
	{
		idx_hist = ft_strdup(config->history[i - 1]);
		i = ft_strlen(pre) + ft_strlen(idx_hist) + ft_strlen(su);
		ret_hist = ft_strnew(++i);
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
