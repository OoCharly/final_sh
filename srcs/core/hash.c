/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 08:32:24 by tboos             #+#    #+#             */
/*   Updated: 2016/12/07 11:56:48 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_bin(char *path, t_dirent tdir, t_bin **pbin)
{
	t_st	st;
	t_bin	bin;
	char	*fpath;

	fpath = ft_strslashjoin(path, tdir.d_name);
	if (!fpath)
		return(-1);
	if (stat(fpath, &st) || !S_ISREG(st.st_mode))
		return (!ft_freegiveone((void**)&fpath));
	if (!(bin.name = ft_strdup(tdir.d_name)))
		return (-1);
	bin.path_name = fpath;
	if (!(*pbin = ft_memmove(ft_memalloc(sizeof(t_bin)), &bin, sizeof(t_bin))))
		free(bin.name);
	return ((pbin) ? 0 : -1);
}

static void	ft_bin_insert(DIR *dir, char *path, t_config *config)
{
	t_dirent	*dirent;
	t_bin		*bin;
	t_list		*new;

	while ((dirent = readdir(dir)))
	{
		bin = NULL;
		if ((check_bin(path, *dirent, &bin)))
			ft_error(SHNAME, NULL, "error creating path to bin", CR_ERROR);
		if (bin)
		{
			if(!(new = ft_lstnew(bin, sizeof(t_bin))))
			{
				ft_freebin(bin, sizeof(t_bin));
				ft_error(SHNAME, NULL, "error creating path to bin", CR_ERROR);
			}
			ft_sorted_list_insert(&(config->bin), new, &ft_ascii_cmp);
		}
	}
}

static int	ft_create_list_bin(char *path, t_config *config)
{
	char		*dirpath;
	char		*kill;
	DIR			*dir;

	if (!(path = ft_strchr(path, '=')) || !*(++path)
			|| !(path = ft_strdup(path)))
		return (0);
	kill = path;
	while ((dirpath = path))
	{
		if ((path = ft_strchr(path, ':')))
			*(path++) = 0;
		if (!access(dirpath, R_OK | X_OK) && (dir = opendir(dirpath)))
		{
			ft_bin_insert(dir, dirpath, config);
			closedir(dir);
		}
	}
	ft_freegiveone((void**)&kill);
	return (1);
}

int			ft_pathtohash(t_config *config)
{
	char	*path;
	short	index;
	t_list	*rabbit;
	char	c;

	if (config->bin)
		ft_lstdel(&(config->bin), &ft_freebin);
	if ((path = ft_strtabfindstart(config->env, "PATH=")))
	{
		ft_free(config->last_hash);
		config->last_hash = ft_strdup(path);
		if (!(ft_create_list_bin(path, config)))
			return (0);
		rabbit = config->bin;
		c = 'a';
		index = 0;
		while (index < 34)
		{
			config->h_bin[index] = rabbit;
			while (rabbit && (((t_bin *)rabbit->data)->name[0] < c))
				rabbit = rabbit->next;
			index++;
			c++;
		}
	}
	return (1);
}

int			ft_return_binpath(t_config *config, char *name, char **fpath)
{
	t_list	*archer;
	int		i;

	*fpath = NULL;
	if (config->bin)
	{
		i = (name[0] < 'a' ? 0 : name[0] - 'a' + 1);
		i = (i > 33 ? 33 : i);
		archer = config->h_bin[i];
		while (archer && (((t_bin *)archer->data)->name[0] - 'a') < i
				&& ft_strcmp(name, ((t_bin *)archer->data)->name))
			archer = archer->next;
		if (archer && !(ft_strcmp(name, ((t_bin *)archer->data)->name)))
		{
			*fpath = ((t_bin *)archer->data)->path_name;
			if (!access(*fpath, X_OK))
				return (0);
		}
	}
	return (-1);
}
