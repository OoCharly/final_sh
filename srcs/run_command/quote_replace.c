/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:21:44 by tboos             #+#    #+#             */
/*   Updated: 2016/12/14 17:15:57 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_quote_replace(char **t, t_list *next)
{
	int			i;
	size_t		j;

	i = -1;
	while (t[++i])
	{
		j = -1;
		while (t[i][++j])
			if (t[i][j] == '\'' || t[i][j] == '\"')
				j = ft_dodge_quote(t[i], j);
		j = -1;
		while (t[i][++j])
			if (t[i][j] == '\\')
				j++;
			else if (t[i][j] == '\'' || t[i][j] == '\"')
			{
				ft_memmove(t[i] + j, t[i] + j + 1, ft_strlen(t[i] + j));
				j--;
			}
	}
	return (next);
}

static t_list	*ft_quote_handle(t_list *next, t_config *config)
{
	char		**t;
	int			i;
	size_t		j;

	if (!next || !next->data)
		return (next);
	t = (char **)next->data;
	i = -1;
	while (t[++i])
	{
		j = 0;
		while (t[i][j])
		{
			if ((t[i][j] == '~' || t[i][j] == '$')
				&& !(t[i] = ft_envvarinsert(t[i], &j, config)))
				return (NULL);
			else if (t[i][j] == '\'')
				j = ft_dodge_quote(t[i], j);
			else if (t[i][j] == '\\')
				j += 2;
			else
				++j;
		}
	}
	return (ft_quote_replace(t, next));
}

int				ft_quote(t_list *begin, t_config *config)
{
	while (begin)
	{
		if (!begin->data_size && !ft_quote_handle(begin, config))
			return (0);
		else if (begin->data_size == SSHELL && !ft_quote(begin->data, config))
			return (0);
		begin = begin->next;
	}
	return (1);
}
