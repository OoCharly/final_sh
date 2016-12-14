/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:01:07 by jmunoz            #+#    #+#             */
/*   Updated: 2016/12/14 13:44:31 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If the brace is closed later, return the index of closing brace.
** If not, return 0.
*/

int			ft_isbraces(char *str)
{
	int		open;
	int		close;
	int		i;

	open = 0;
	close = 0;
	i = -1;
	while (str[++i])
	{
		if ((!i && str[i] == '{') || (i && str[i] == '{' && str[i - 1] != '\\'))
			open++;
		if ((!i && str[i] == '}') || (i && str[i] == '}' && str[i - 1] != '\\'))
			close++;
		if (open == close)
			return (i);
	}
	return (0);
}

/*
**Checks if there are one of the following globbing pathern in arg : *[]?
*/

int			ft_checkglob(char *arg)
{
	char	*glob;
	char	*ret;
	char	*tmp;

	tmp = arg;
	glob = "*[]?\0";
	while (*glob)
	{
		while ((ret = ft_strchr(tmp, *glob)))
		{
			if ((ft_strcmp(ret, tmp) && *(ret - 1) != '\\')
					|| (!ft_strcmp(ret, tmp)))
				return (1);
			tmp = ret + 1;
		}
		glob++;
	}
	return (0);
}

/*
** If list is made of strings, get the total length of the list in char, adding
** one space between each string.
*/

size_t		ft_size_list(t_list *begin)
{
	int i;

	i = 0;
	while (begin)
	{
		i += ft_strlen(begin->data) + 1;
		begin = begin->next;
	}
	return (i);
}
