/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:14:57 by tboos             #+#    #+#             */
/*   Updated: 2017/01/09 06:05:00 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_separator(char c)
{
	if (c == ';')
		return (1);
	if (c == '&')
		return (1);
	if (c == '|')
		return (1);
	if (ft_isspace(c))
		return (1);
	return (0);
}

/*
** Define COMP_BEGIN with strsub. It represent the needle to look for.
*/

char	*get_begin(int i, char *str, size_t *len)
{
	while (i >= 0 && !ft_is_separator(str[i]))
	{
		i -= 1;
		*len += 1;
	}
	return (str + i + 1);
}
