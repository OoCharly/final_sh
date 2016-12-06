/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             */
/*   Updated: 2016/02/22 21:11:58 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s2 || !(*s2))
		return ((char *)s1);
	while (*s1 && n)
	{
		i = 0;
		if (*s1 == *s2)
			while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
				i++;
		if (s2[i] == '\0')
			return ((char *)s1);
		s1++;
		n--;
	}
	return (NULL);
}
