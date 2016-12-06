/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:20:38 by jmunoz            #+#    #+#             */
/*   Updated: 2016/11/25 21:23:41 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globbing.h"

/*
** Check if there is a couple of brackets.
** Verify the validity of the brackets possibility to c.
** Leave the string on the last bracket.
*/

static int		brackets(char **glob, char c)
{
	int			min;
	int			match;

	match = 0;
	if (!ft_strchr(*glob, ']'))
		return (0);
	while (**glob != ']' && !match)
	{
		if (*(*glob + 1) && *(*glob + 2) && *(*glob + 1) == '-' &&
		*(*glob + 2) != ']')
		{
			min = (int)**glob - 1;
			while (++min <= (int)*(*glob + 2) && !match)
				if ((int)c == min)
					match = 1;
			*glob += 2;
		}
		else if (**glob == c)
			match = 1;
		(*glob)++;
	}
	while (**glob != ']')
		(*glob)++;
	return (match);
}

/*
** Check the validity of a glob string to a string.
** * => any number of any char including none.
** ? => any char.
** [abc] => one of the embedded char.
** [a-z] => one char in the range.
*/

int				ft_match(char *glob, char *comp)
{
	if (*comp && *glob == '*')
		return (ft_match(glob + 1, comp) || ft_match(glob, comp + 1));
	if ((!*comp || *comp == '/') && *glob == '*')
		return (ft_match(glob + 1, comp));
	if ((!*comp || *comp == '/') && (!*glob || *glob == '/'))
		return (1);
	if ((*comp == *glob || *glob == '?' || (*glob == '[' &&
	brackets(&glob, *comp))) && *comp && *comp != '/' && *glob && *glob != '/')
		return (ft_match(glob + 1, comp + 1));
	return (0);
}
