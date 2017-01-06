/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:01:07 by jmunoz            #+#    #+#             */
/*   Updated: 2017/01/05 14:43:17 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Search the position of the closing char from the first opening char (must be
** included). Return its position. If not found return 0.
** c[0] = opening char.
** c[1] = closing char.
*/

int			ft_closechar(char *arg, char *c)
{
	int		i;
	char	flag;
	char	open;

	flag = 0;
	i = 0;
	open = 0;
	while (arg[i])
	{
		if (arg[i] == '\\')
				i++;
		else if ((arg[i] == '\'' && flag != '\"')
		|| (arg[i] == '\"' && flag != '\''))
			flag = (flag) ? 0 : arg[i];
		else if (arg[i] == c[0] && !flag)
			open++;
		else if (arg[i] == c[1] && !flag)
			open--;
		if (arg[i] == c[1] && !flag && !open)
			return (i);
		i++;
	}
	return (0);
}

/*
**Checks if there are one of the following globbing pathern in arg : *[]?
**Return pos of pattern + 1. If not return 0;
*/

int				ft_checkchars(char *tmp, char *chars)
{
	char	*arg;
	char	flag;
	int		i;

	while (*chars)
	{
		flag = 0;
		arg = tmp;
		i = 0;
		while (arg[i])
		{
			if (arg[i] == '\\')
				i++;
			else if ((arg[i] == '\'' && flag != '\"')
			|| (arg[i] == '\"' && flag != '\''))
				flag = (flag) ? 0 : arg[i];
			else if (arg[i] == *chars && !flag)
				return (i + 1);
			i++;
		}
		chars++;
	}
	return (0);
}

/*
** If list is made of strings, get the total length of the list in char, adding
** one space between each string.
*/

size_t			ft_size_list(t_list *begin)
{
	size_t	i;

	i = 0;
	while (begin)
	{
		i += ft_strlen(begin->data) + 1;
		begin = begin->next;
	}
	return (i);
}
