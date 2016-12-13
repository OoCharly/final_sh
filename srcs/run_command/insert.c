/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:58:11 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/13 20:08:04 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes begin->data for a new char **, in this one an new char * was insert
** wich contents the result of globbing or of the history index search (!).
*/

static void	ft_insert(t_config *config, char ***t, int *i, int mode)
{
	char	*tmp;
	char	**g_tab;
	char	**kill;

	if (!mode)
		tmp = ft_create_strhistidx(config, (*t)[*i]);
	else if (mode == 1)
		tmp = ft_launchbraces((*t)[*i]);
	else
		tmp = ft_launch_glob((*t)[*i]);
	if (tmp)
	{
		g_tab = ft_strsplit(tmp, ' ');
		ft_freegiveone((void **)&tmp);
		kill = *t;
		*t = ft_insertdeletetab(*t, g_tab, *i);
		*i += ft_strtablen(g_tab);
		ft_free(g_tab);
		ft_free(kill);
	}
	else
		(*i)++;
}

/*
** For each mode (braces, bang, glob) check if there is things to replace for
** every piece of argument.
*/

void		ft_check_insert(t_config *config, char ***t, int mode)
{
	int i;

	i = 0;
	while ((*t)[i])
	{
		if (!mode)
			ft_insert(config, t, &i, mode);
		else if (mode == 1 && ft_checkhist((*t)[i]))
			ft_insert(config, t, &i, mode);
		else if (mode == 2 && ft_checkglob((*t)[i]))
			ft_insert(config, t, &i, mode);
		else
			i++;
	}
}

/*
** Runs throught config->chimera, on any begin->data wich is not an operator
** checks if there are a globing pathern or an '!'. If one of these pathern
** is found launch the corresponding function.
*/

int			ft_insert_loop(t_list *begin, t_config *config)
{
	char	**t;
	int		j;

	while (begin)
	{
		if (!begin->data_size && !(j = 0))
		{
			t = ((char **)begin->data);
			while (j < 3)
				ft_check_insert(config, &t, j++);
			begin->data = t;
		}
		begin = begin->next;
	}
	return (1);
}
