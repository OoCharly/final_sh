/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:02:24 by tboos             #+#    #+#             */
/*   Updated: 2017/01/04 16:10:43 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_isop(char c)
{
	static char	*str = "_><|&;`\\()[]{}'#=";

	return (c ? ft_strchr(str, c) : NULL);
}

static char	*ft_varsearch(char *cmd, size_t *i, t_config *config, char *m)
{
	char	c;
	char	*e;

	*i += 1;
	if (cmd[(*i)] == '$' && (*i)++)
		e = ft_itoa(getpid());
	else if (cmd[(*i)++] == '?')
		e = ft_itoa(config->last_exit);
	else
	{
		while (cmd[*i] && (ft_isalnum(cmd[*i]) || ft_isop(cmd[*i])))
			++(*i);
		c = cmd[*i];
		cmd[*i] = 0;
		e = ft_getenv(m, config->env);
		cmd[*i] = c;
	}
	return (e);
}

char		*ft_envvarinsert(char *cmd, size_t *i, t_config *config)
{
	char		*m;
	char		*e;

	if (ft_isop(cmd[*i + 1]) && ++(*i))
		return (cmd);
	m = cmd + *i + 1;
	if (cmd[*i] == '~')
	{
		if ((cmd[1] && cmd[1] != '/') || *i)
			return (cmd);
		e = ft_strtabfind(config->env, "HOME=");
		if (e)
			e += 5;
		++(*i);
	}
	else
		e = ft_varsearch(cmd, i, config, m);
	ft_memmove((void *)(m - 1), (void *)(cmd + *i), ft_strlen(cmd + *i) + 1);
	*i = *i + ft_strlen(e);
	if (!e)
		return (cmd);
	if (e && (e = ft_strinsert(cmd, e, m - 1)) && ft_freegiveone((void**)&cmd))
		return (e);
	ft_error(SHNAME, "lexer", "malloc error", CR_ERROR);
	return (NULL);
}
