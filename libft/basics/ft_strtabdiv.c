/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdiv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:30:40 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:30:54 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strtabdiv(char **tab, char *needle)
{
	char	**div;
	int		i;

	if (!tab | !*tab || !needle || !*needle)
		return (NULL);
	i = -1;
	div = tab;
	while (div[++i])
		if (!ft_strcmp(div[i], needle))
			break ;
	if (!div[i])
		return (NULL);
	free(div[i]);
	div[i] = NULL;
	if (!div[++i] || !(div = ft_strtabdup(&(div[i]))))
		return (NULL);
	return (div);
}
