/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:25:11 by cdesvern          #+#    #+#             */
/*   Updated: 2016/12/13 10:46:16 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Checks if there are one of the following globbing pathern in arg : *[]?
*/

int			ft_checkglob(char *arg)
{
	char	*glob;
	char	*ret;
	char	*tmp;

	tmp = arg;
	glob = "*[]?\n";
	while (*glob)
	{
		while ((ret = ft_strchr(tmp, *glob)))
		{
			if ((ft_strcmp(ret, tmp) && *(ret - 1) != '\\')
					|| (!ft_strcmp(ret, tmp)))
				return (1);
			tmp = ret + 1;
		}
		glob++;
	}
	return (0);
}

int			ft_insertglob(t_list *begin)
{
	int		i;
	char	**t;
	char	*tmp;
	char	**g_tab;
	char	**tmp_tab;

	while (begin)
	{
		if (!begin->data_size)
		{
			t = ((char **)begin->data);
			i = 0;
			while (t[i])
				if (!ft_checkglob(t[i]) || !(tmp = ft_launch_glob(t[i])))
					i++;
				else 
				{
					g_tab = ft_strsplit(tmp, ' ');
					ft_freegiveone((void **)&tmp);
					tmp_tab = t;
					t = ft_insertdeletetab(t, g_tab, i);
					i += ft_strtablen(g_tab);
					ft_free(g_tab);
					ft_free(tmp_tab);
				}
			begin->data = t;
		}
		begin = begin->next;
	}
	return (1);
}

int		ft_insertbraces(t_list *begin)
{
	int		i;
	char	**new_tab;
	char	**t;
	char	**tmp_tab;

	while (begin)
	{
		if (!begin->data_size)
		{
			t = ((char **)begin->data);
			i = 0;
			while (t[i])
				if (!(new_tab = ft_launchbraces(t[i])))
					i++;
				else
				{
					tmp_tab = t;
					t = ft_insertdeletetab(t, new_tab, i);
					i += ft_strtablen(new_tab);
					ft_free(new_tab);
					ft_free(tmp_tab);
				}
			begin->data = t;
		}
		begin = begin->next;
	}
	return (1);
}
