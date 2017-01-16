/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:27:02 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:27:17 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strtabtotallen(char **tab)
{
	size_t len;

	len = 0;
	while (*tab)
	{
		len += ft_strlen(*tab);
		++tab;
	}
	return (len);
}

char	*ft_strtabchrjoin(char **tab, char c)
{
	size_t	len;
	char	*result;

	if (!(len = ft_strtabtotallen(tab))
		|| !(result = ft_memalloc(len + (c ? ft_strtablen(tab) : 0) + 1)))
		return (NULL);
	len = 0;
	while (*tab)
	{
		ft_strcpy(result + len, *tab);
		len += ft_strlen(*tab);
		if (c)
		{
			result[len] = c;
			++len;
		}
		++tab;
	}
	return (result);
}

char	**ft_strtabjoin(char **t1, char **t2)
{
	int		len;
	int		i;
	char	**result;

	if (!t1 || !t2)
		return (t1 ? t1 : t2);
	len = ft_strtablen(t1) + ft_strtablen(t2);
	if (!(result = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = 0;
	while (t1[i])
	{
		result[i] = t1[i];
		++i;
	}
	len = 0;
	while (t2[len])
	{
		result[i] = t2[len++];
		++i;
	}
	return (result);
}

char	**ft_strtabjoin_free(char **t1, char **t2)
{
	char	**result;

	result = ft_strtabjoin(t1, t2);
	ft_freegiveone((void**)&t1);
	ft_freegiveone((void**)&t2);
	return (result);
}
