/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:24:44 by cdesvern          #+#    #+#             */
/*   Updated: 2016/12/14 19:24:28 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_char_clean(char *str, char c)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == '\\')
			str++;
		else if (*str == c)
			ft_memmove(str, str + 1, ft_strlen(str));
		str++;
	}
}

void	ft_tabchar_clean(char **str, char c)
{
	if (!str)
		return ;
	while (*str)
	{
		ft_char_clean(*str, c);
		str++;
	}
}

void	ft_tabstr_clean(char **str, char *tok)
{
	while (*tok)
	{
		ft_tabchar_clean(str, *tok);
		tok++;
	}
}
