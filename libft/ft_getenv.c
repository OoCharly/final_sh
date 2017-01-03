/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 14:07:23 by cdesvern          #+#    #+#             */
/*   Updated: 2017/01/03 14:48:42 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_igetenv(char *name, char **env)
{
	char	*np;
	char	**p;
	char	*cp;
	int		len;

	if (!(np = name) || !env)
		return (-1);
	while (*np && *np != '=')
		np++;
	len = (int)(np - name) + 1;
	p = env;
	while ((cp = *p) != NULL)
	{
		np = name;
		if (ft_strncmp(cp, np, len) == 61)
			return ((int)(p - env));
		else
			p++;
	}
	return (-1);
}
char	*ft_getenv_whole(char *name, char **env)
{
	char	*np;
	char	**p;
	char	*cp;
	int		len;

	if (!(np = name) || !env)
		return (NULL);
	while (*np && *np != '=')
		np++;
	len = (int)(np - name) + 1;
	p = env;
	while ((cp = *p) != NULL)
	{
		np = name;
		if (ft_strncmp(cp, np, len) == 61)
			return (cp);
		else
			p++;
	}
	return (NULL);
}

char	*ft_getenv(char *name, char **env)
{
	char	*np;
	char	**p;
	char	*cp;
	int		len;

	if (!(np = name) || !env)
		return (NULL);
	while (*np && *np != '=')
		np++;
	len = (int)(np - name) + 1;
	p = env;
	while ((cp = *p) != NULL)
	{
		np = name;
		if (ft_strncmp(cp, np, len) == 61)
			return (cp + len);
		else
			p++;
	}
	return (NULL);
}
