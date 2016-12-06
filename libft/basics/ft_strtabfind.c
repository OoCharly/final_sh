/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabfind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:06:09 by tboos             #+#    #+#             */
/*   Updated: 2016/11/11 14:12:54 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strtabifindstart(char **tab, char *needle)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(needle);
	while (tab && tab[i])
	{
		if (!ft_strncmp(tab[i], needle, len))
			return (i);
		i++;
	}
	return (-1);
}

int		ft_strtabifind(char **tab, char *needle)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (ft_strstr(tab[i], needle))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strtabfindstart(char **tab, char *needle)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(needle);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], needle, len))
			return (tab[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strtabfind(char **tab, char *needle)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (ft_strstr(tab[i], needle))
			return (tab[i]);
		i++;
	}
	return (NULL);
}
