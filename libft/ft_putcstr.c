/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 08:38:51 by tboos             #+#    #+#             */
/*   Updated: 2016/03/16 12:41:19 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrpad_fd(char *str, int size, char pos, int fd)
{
	char	tab[512];
	int		i;

	if (size < 512 && size > 0)
	{
		i = -1;
		if (pos == 'L')
			while (*str && ++i < size)
				tab[i] = *(str++);
		while (++i < size)
			tab[i] = ' ';
		if (pos == 'R')
		{
			i = size - ft_strlen(str) - 1;
			while (*str && ++i < size)
			{
				tab[i] = *str;
				str++;
			}
		}
		tab[size] = '\0';
		ft_putstr_fd(tab, fd);
	}
}

void	ft_putstrpad(char *str, int size, char pos)
{
	char	tab[512];
	int		i;

	if (size < 512 && size > 0)
	{
		i = -1;
		if (pos == 'L')
			while (*str && ++i < size)
				tab[i] = *(str++);
		while (++i < size)
			tab[i] = ' ';
		if (pos == 'R')
		{
			i = size - ft_strlen(str) - 1;
			while (*str && ++i < size)
			{
				tab[i] = *str;
				str++;
			}
		}
		tab[size] = '\0';
		ft_putstr(tab);
	}
}

void	ft_putcstr(char *str, char c, int size, char pos)
{
	char	tab[512];
	int		i;

	if (size < 512 && size > 0)
	{
		i = -1;
		if (pos == 'L')
			while (*str && ++i < size)
				tab[i] = *(str++);
		while (++i < size)
			tab[i] = c;
		if (pos == 'R')
		{
			i = size - ft_strlen(str) - 1;
			while (*str && ++i < size)
			{
				tab[i] = *str;
				str++;
			}
		}
		tab[size] = '\0';
		ft_putstr(tab);
	}
}
