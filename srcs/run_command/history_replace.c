/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:06:06 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/12 16:22:02 by maxpetit         ###   ########.fr       */
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

/*
**Returns the index which is after the charactere '!', if no '!' are found or
**if only '!' precedated by '\' are found return -1.
*/

static int	ft_parse_hist(char *str)
{
	int		i;
	int		j;
	int		idx;
	char	*idx_str;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '!' && (i == 0 || str[i - 1] != '\\'))
		{
			idx = ++i;
			while (str[i] && ft_isdigit(str[i++]))
				j++;
			idx_str = ft_strnew(j);
			j = -1;
			while (str[idx] && ft_isdigit(str[idx]))
				idx_str[++j] = str[idx++];
			return (ft_atoi(idx_str));
		}
	}
	return (-1);
}

char		*ft_ret_indexhist(t_config *config, char *str)
{
	int		idx;

	idx = ft_parse_hist(str);
	if (idx != -1)
		return (ft_strdup(config->history[idx - 1]));
	return (NULL);
}
