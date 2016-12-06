/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 08:32:24 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:18:43 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_return_binpath(t_config *config, char *name)
{
	t_list	*archer;
	int		i;

	if (config->bin)
	{
		i = (name[0] < 'a' ? 0 : name[0] - 'a' + 1);
		i = (i > 33 ? 33 : i);
		archer = config->h_bin[i];
		while (archer && (((t_bin *)archer->data)->name[0] - 'a') < i
				&& ft_strcmp(name, ((t_bin *)archer->data)->name))
			archer = archer->next;
		if (archer && !(ft_strcmp(name, ((t_bin *)archer->data)->name)))
			return (((t_bin *)archer->data)->path_name);
	}
	return (NULL);
}

static void	ft_hash_bin(t_config *config)
{
	short	index;
	t_list	*rabbit;
	char	c;

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

static void	ft_bin_insert(DIR *dir, char *path, t_config *config)
{
	t_dirent	*dirent;
	t_bin		bin;
	t_list		*new;

	while ((dirent = readdir(dir)))
	{
		if (!(bin.path_name = ft_strslashjoin(path, dirent->d_name))
				|| !(bin.name = ft_strrchr(bin.path_name, '/'))
				|| !(++(bin.name))
				|| !(new = ft_lstnew(ft_memmove(ft_memalloc(sizeof(t_bin)),
				&bin, sizeof(t_bin)), sizeof(t_bin))))
			ft_error(SHNAME, NULL, "error creating path to bin", CR_ERROR);
		else if (!ft_strcmp(dirent->d_name, ".")
				|| !ft_strcmp(dirent->d_name, ".."))
			ft_lstdel(&new, &ft_freebin);
		else if (new->data)
			ft_sorted_list_insert(&(config->bin), new, &ft_ascii_cmp);
		else
			free(new);
	}
}

static int	ft_create_list_bin(char *path, t_config *config)
{
	char	*dirpath;
	char	*kill;
	DIR		*dir;

	if (!(path = ft_strchr(path, '=')) || !*(++path)
		|| !(path = ft_strdup(path)))
		return (0);
	kill = path;
	while ((dirpath = path))
	{
		path = ft_strchr(path, ':');
		if (path && (++path))
			*(path - 1) = '\0';
		if ((dir = opendir(dirpath)))
		{
			ft_bin_insert(dir, dirpath, config);
			closedir(dir);
		}
	}
	free(kill);
	return (1);
}

int			ft_pathtohash(t_config *config)
{
	char	*path;

	if (config->bin)
		ft_lstdel(&(config->bin), &ft_freebin);
	if ((path = ft_strtabfindstart(config->env, "PATH=")))
	{
		if (!(ft_create_list_bin(path, config)))
			return (0);
		ft_hash_bin(config);
	}
	return (1);
}
