/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_res_symlink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:01:37 by cdesvern          #+#    #+#             */
/*   Updated: 2017/02/17 14:33:59 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_absolute_link(char *slash2, char *cp, char **result)
{
	char	*kill;

	kill = *result;
	*result = ft_strchrjoin(cp, '/', slash2 + 1);
	ft_freegiveone((void**)&kill);
	return (ft_strlen(cp) + 1);
}

static size_t	ft_relative_link(char *slash1, char *slash2, char *cp,
		char **result)
{
	char	*kill;
	size_t	i;

	kill = *result;
	slash1[1] = 0;
	slash1 = ft_strjoin(kill, cp);
	i = ft_strlen(slash1 + 1);
	if (slash2)
	{
		*result = ft_strchrjoin(slash1, '/', slash2 + 1);
		ft_freegiveone((void**)&slash1);
	}
	else
		*result = slash1;
	ft_freegiveone((void**)&kill);
	return (i);
}

char			*ft_resolve_symlink(char *path)
{
	char	*slash1;
	char	*slash2;
	char	cp[_POSIX_PATH_MAX + 1];
	char	*result;
	size_t	i;

	result = path;
	if ((slash1 = ft_strchr(path, '/')))
		while ((slash2 = ft_strchr(slash1 + 1, '/')))
		{
			ft_bzero(&cp, _POSIX_PATH_MAX + 1);
			*slash2 = 0;
			if (readlink(result, cp, _POSIX_PATH_MAX) < 0 && (slash1 = slash2)
					&& (*slash2 = '/'))
				continue ;
			i = (cp[0] == '/') ? ft_absolute_link(slash2, cp, &result)
				: ft_relative_link(slash1, slash2, cp, &result);
			slash1 = result + i + 1;
		}
	if (!(slash1[1] && readlink(result, cp, _POSIX_PATH_MAX) >= 0))
		return (result);
	if (cp[0] == '/' && ft_freegiveone((void**)&result))
		return (ft_strdup(cp));
	ft_relative_link(slash1, NULL, cp, &result);
	return (result);
}
