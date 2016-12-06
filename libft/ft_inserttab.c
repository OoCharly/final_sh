/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inserttab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:56:14 by cdesvern          #+#    #+#             */
/*   Updated: 2016/12/06 13:56:17 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>

/*
** Insert new table inside an existing table from a given index
*/

char    **ft_inserttab(char **big, char **small, size_t index)
{
        size_t  total_len;
        char    **new;
        int             i;
        size_t  tmp;

        if (!big || !*big)
                return (small);
        if (!small || !*small)
                return (big);
        total_len = ft_strtablen(big) + ft_strtablen(small);
        if (!(new = (char**)ft_memalloc(sizeof(char*) * total_len + 1)))
                return (NULL);
        i = -1;
        while (++i < (int)index && big[i])
                new[i] = big[i];
        index = i;
        i = 0;
        tmp = index;
        while (small[i])
                new[index++] = small[i++];
        while (big[tmp])
                new[index++] = big[tmp++];
        return (new);
}

char    **ft_insertdeletetab(char **big, char **small, size_t index)
{
        size_t  total_len;
        char    **new;
        int     i;
        size_t  tmp;

        if (!big || !*big)
                return (small);
        if (!small || !*small)
                return (big);
        total_len = ft_strtablen(big) + ft_strtablen(small);
        if (!(new = (char**)ft_memalloc(sizeof(char*) * (total_len + 1))))
                return (NULL);
        i = -1;
        while (++i < (int)index && big[i])
                new[i] = big[i];
        index = i;
        i = 0;
        tmp = (big[i]) ? index : index - 1;
        while (small[i])
                new[index++] = small[i++];
		while (big[tmp])
				new[index++] = big[++tmp];
	//	new[total_len] = NULL;
        return (new);
}
