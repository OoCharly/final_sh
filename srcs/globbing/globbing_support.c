/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:01:07 by jmunoz            #+#    #+#             */
/*   Updated: 2017/01/04 21:35:20 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int i;

	i = 0;
	while (begin)
	{
		i += ft_strlen(begin->data) + 1;
		begin = begin->next;
	}
	return (i);
}
