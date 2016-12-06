/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             */
/*   Updated: 2016/09/14 12:29:42 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;

	if (!needle || !(*needle))
		return ((char *)haystack);
	while (*haystack)
	{
		i = 0;
		if (*haystack == *needle)
			while (haystack[i] == needle[i] && needle[i] && haystack[i])
				i++;
		if (needle[i] == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

int		ft_strstri(const char *haystack, const char *needle)
{
	size_t		i;
	int			index;

	if (!needle || !(*needle))
		return (-1);
	index = 0;
	while (*haystack)
	{
		i = 0;
		if (*haystack == *needle)
			while (haystack[i] == needle[i] && needle[i] && haystack[i])
				i++;
		if (needle[i] == '\0')
			return (index);
		haystack++;
		index++;
	}
	return (-1);
}
