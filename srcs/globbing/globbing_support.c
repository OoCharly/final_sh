/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:01:07 by jmunoz            #+#    #+#             */
/*   Updated: 2016/12/15 18:10:00 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If the brace is closed later, return the index of closing brace.
** If not, return 0.
*/

int				ft_isbraces(char *str)
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

int				ft_checkchars(char *tmp, char *chars)
{
	char	*arg;
	char	flag;

	while (*chars)
	{
		flag = 0;
		arg = tmp;
		while (*arg)
		{
			if (*arg == '\\')
				arg++;
			else if ((*arg == '\'' && flag != '\"')
			|| (*arg == '\"' && flag != '\''))
				flag = (flag) ? 0 : *arg;
			else if (*arg == *chars && !flag)
				return (1);
			arg++;
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
