/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:32:40 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:32:51 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrtab_fd(char **s, char c, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putstr_fd(s[i], fd);
		if (s[i + 1])
			ft_putchar_fd(c, fd);
		++i;
	}
}

void	ft_putstrtab(char **s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putstr(s[i]);
		if (s[i + 1])
			ft_putchar(c);
		++i;
	}
}
