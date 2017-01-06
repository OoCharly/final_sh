/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:16:50 by jmunoz            #+#    #+#             */
/*   Updated: 2017/01/05 12:26:55 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** store every variable specified in a array.
*/

char		**ft_getenvtab(char *str, char **e)
{
	char	*ret;

	if (!e)
		return (NULL);
	ret = ft_getenv(str, e);
	if (ret == NULL)
		return (NULL);
	return (ft_strsplit(ret + 1, ':'));
}

/*
** size number of elem for each row : COMP_IN_COL.
*/

void		get_col_elem(t_stream *stream)
{
	size_t col_nb;

	col_nb = (COMP_COL + 1) / (COMP_PAD + 2);
	if (COMP_SIZE_LIST > col_nb)
	{
		if (!(COMP_SIZE_LIST % col_nb))
			COMP_IN_COL = COMP_SIZE_LIST / col_nb;
		else
			COMP_IN_COL = (COMP_SIZE_LIST / col_nb) + 1;
	}
	else
		COMP_IN_COL = 1;
}

/*
** Get max size for padding.
*/

void		get_pad(t_stream *stream, char *str)
{
	size_t	size;

	if ((size = ft_strlen(str) + 1) > COMP_PAD)
		COMP_PAD = size;
}

/*
** Size list in COMP_SIZE_LIST.
*/

void		get_size_list(t_stream *stream)
{
	t_list	*list;
	size_t	i;

	if (COMP_BEGIN_LIST)
	{
		i = 1;
		list = COMP_BEGIN_LIST;
		while (list->next)
		{
			i++;
			list = list->next;
		}
		COMP_SIZE_LIST = i;
	}
}
