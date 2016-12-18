/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:58:11 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/18 15:21:50 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes begin->data for a new char **, in this one an new char * was insert
** wich contents the result of globbing or of the history index search (!).
*/

static void	ft_insert(char ***t, int *i, int mode)
{
	char	*tmp;
	char	**g_tab;
	char	**kill;

	if (!mode)
		tmp = ft_create_strhistidx((*t)[*i]);
	else if (mode == 1)
		tmp = ft_launchbraces((*t)[*i]);
	else
		tmp = ft_launch_glob((*t)[*i]);
	if (tmp)
	{
		g_tab = ft_strsplit(tmp, -1);
		ft_freegiveone((void **)&tmp);
		kill = *t;
		*t = ft_insertdeletetab(*t, g_tab, *i);
		*i += ft_strtablen(g_tab);
		ft_free(g_tab);
		ft_free(kill);
	}
	else
	{
		ft_cleancmd((*t)[*i]);
		(*i)++;
	}
}

/*
** For each mode (braces, bang, glob) check if there is things to replace for
** every piece of argument. Return 1 if t have been modified, 0 else.
*/

int		ft_check_insert(char ***t, int mode)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while ((*t)[i])
	{
		if (!mode && ft_checkhist((*t)[i]))
			ft_insert(t, &i, mode);
		else if (mode == 1 && ft_checkchars((*t)[i], "{}"))
			ft_insert(t, &i, mode);
		else if (mode == 2)
		{
			if (ft_checkchars((*t)[i], "*[]?"))
				ft_insert(t, &i, mode);
			else
			{
				ft_cleancmd((*t)[i]);
				i++;
				j++;
			}
		}
		else
		{
			i++;
			j++;
		}
	}
	return ( (i == j) ? 0 : 1);
}

/*
** Runs throught config->chimera, on any begin->data wich is not an operator
** checks if there are a globing pathern or an '!'. If one of these pathern
** is found launch the corresponding function.
*/

int			ft_insert_loop(t_list *begin)
{
	char	**t;
	int		j;

	while (begin)
	{
		if (!begin->data_size && !(j = 0))
		{
			t = ((char **)begin->data);
			while (j < 3)
				ft_check_insert(&t, j++);
			begin->data = t;
		}
		begin = begin->next;
	}
	return (1);
}
