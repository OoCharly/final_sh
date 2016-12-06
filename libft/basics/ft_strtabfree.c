/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 01:02:33 by tboos             #+#    #+#             */
/*   Updated: 2016/12/06 15:57:17 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtabfree_content(char **tab)
{
	size_t	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
	}
}

void	ft_strtabfree(char **tab)
{
	size_t	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}
