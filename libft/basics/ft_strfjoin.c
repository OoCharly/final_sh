/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 13:00:18 by cdesvern          #+#    #+#             */
/*   Updated: 2016/05/25 13:03:40 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfjoin(char *s1, char *s2, int opt)
{
	char	*out;

	out = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!out)
		return (NULL);
	ft_strcat(ft_strcat(out, s1), s2);
	if (s1 && (opt & 1))
		free(s1);
	if (s2 && (opt & 2))
		free(s2);
	return (out);
}
