/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 01:03:05 by tboos             #+#    #+#             */
/*   Updated: 2016/03/16 01:03:16 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strtabdup(char **src)
{
	size_t	i;
	char	**dest;

	i = ft_strtablen(src);
	if (!(dest = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		return (NULL);
	while (i--)
		if (!(dest[i] = ft_strdup(src[i])))
		{
			while (dest[++i])
				free(dest[i]);
			free(dest);
			return (NULL);
		}
	return (dest);
}
