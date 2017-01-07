/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:58:11 by maxpetit          #+#    #+#             */
/*   Updated: 2017/01/05 16:40:09 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changes begin->data for a new char **, in this one an new char * was insert
** wich contents the result of globbing or of the history index search (!).
*/

static int	ft_st_checkchars(char *tmp, char *chars)
{
	char	*arg;
	char	flag;
	int		i;

	while (*chars)
	{
		flag = 0;
		arg = tmp;
		i = 0;
		while (arg[i])
		{
			if (arg[i] == '\\')
				i++;
			else if (arg[i] == '\'')			
				flag = (flag) ? 0 : arg[i];
			else if (arg[i] == *chars && !flag)
				return (i + 1);
			i++;
		}
		chars++;
	}
	return (0);

}

static void	ft_insert(char ***t, int *i, int mode)
{
	char	**g_tab;
	char	**kill;

	g_tab = NULL;
	if (mode == 2)
		g_tab = ft_launchbraces((*t)[*i]);
	else
		g_tab = ft_launch_glob((*t)[*i]);
	if (g_tab)
	{
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

int			ft_check_insert(char ***t, int mode, t_config *config)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while ((*t)[i])
	{
		if (mode == 1 && ft_st_checkchars((*t)[i], "~$"))
			ft_quotehandle(&((*t)[i++]), config);
		else if (mode == 2 && ft_checkchars((*t)[i], "{}"))
			ft_insert(t, &i, mode);
		else if (mode == 3)
		{
			if (ft_checkchars((*t)[i], "*[]?"))
				ft_insert(t, &i, mode);
			else if (++j)
				ft_cleancmd((*t)[i++]);
		}
		else if (++j)
			i++;
	}
	return ((i == j) ? 0 : 1);
}

/*
** Runs throug config->chimera, on any begin->data wich is not an operator
** checks if there are a globing pathern or an '!'. If one of these pathern
** is found launch the corresponding function.
*/

int			ft_insert_loop(char ***command, t_config *config)
{
	char	**t;
	int		j;

	j = 0;
	t = *command;
	while (++j < 4)
		ft_check_insert(&t, j, config);
	*command = t;
	return (1);
}
