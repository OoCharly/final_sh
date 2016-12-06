/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:30:28 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**add_tab(char **tab, int size_tab)
{
	char	**new_tab;

	if (!(new_tab = (char**)malloc(sizeof(char*) * (size_tab + 1))))
		return (0);
	new_tab[size_tab] = NULL;
	if (size_tab == 1)
		return (new_tab);
	size_tab -= 2;
	while (size_tab >= 0)
	{
		new_tab[size_tab] = ft_strdup(tab[size_tab]);
		free(tab[size_tab]);
		size_tab--;
	}
	return (new_tab);
}

char			**ft_strsplit(char *s, char c)
{
	char	**tab;
	char	**tabdup;
	int		size;
	int		size_tab;

	tab = NULL;
	size_tab = 0;
	while (*s)
	{
		while (!(size = ft_strlenc((char*)s, c)))
			s++;
		if (size == -1)
			return (tab);
		tabdup = tab;
		tab = add_tab(tab, ++size_tab);
		if (size_tab > 1)
			free(tabdup);
		tab[size_tab - 1] = ft_strncpy(ft_strnew(size), s, size);
		s += size;
	}
	return (tab);
}
