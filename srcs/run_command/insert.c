/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:58:11 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/13 11:17:49 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Changes begin->data for a new char **, in this one an new char * was insert
**wich contents the result of globbing or of the history index search (!).
*/

static void	ft_insert(t_config *config, char ***t, int *i, int mode)
{
	char	*tmp;
	char	**g_tab;
	char	**kill;

	if (!mode)
		tmp = ft_launch_glob((*t)[*i]);
	else
		tmp = ft_ret_indexhist(config, (*t)[*i]);
	g_tab = ft_strsplit(tmp, ' ');
	ft_freegiveone((void **)&tmp);
	kill = *t;
	*t = ft_insertdeletetab(*t, g_tab, *i);
	*i += ft_strtablen(g_tab);
	ft_free(g_tab);
	ft_free(kill);
}

/*
**Runs throught config->chimera, on any begin->data wich is not an operator
**checks if there are a globing pathern or an '!'. If one of these pathern
**is found launch the corresponding function.
*/

int			ft_insert_loop(t_list *begin, t_config *config)
{
	int		i;
	char	**t;

	while (begin)
	{
		if (!begin->data_size && !(i = 0))
		{
			t = ((char **)begin->data);
			while (t[i])
			{
				if (ft_checkglob(t[i]))
					ft_insert(config, &t, &i, 0);
				else if (ft_checkhist(t[i]))
					ft_insert(config, &t, &i, 1);
				else
					i++;
			}
			begin->data = t;
		}
		begin = begin->next;
	}
	return (1);
}
