/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslashjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 08:40:11 by tboos             #+#    #+#             */
/*   Updated: 2017/01/04 20:43:23 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrjoin(char *s1, char c, char *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = (char *)ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	new = ft_strcpy(new, s1);
	new[ft_strlen(new)] = c;
	new = ft_strcat(new, s2);
	return (new);
}

char	*ft_strslashjoin(char *s1, char *s2)
{
	char	*new;

	if (!s1 || !s2 || !(*s1) || !(*s2))
		return (NULL);
	new = (char *)ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	new = ft_strcpy(new, s1);
	new = ft_strcat(new, "/");
	new = ft_strcat(new, s2);
	return (new);
}
