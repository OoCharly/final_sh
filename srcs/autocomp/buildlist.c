/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:27:31 by tboos             #+#    #+#             */
/*   Updated: 2016/12/13 16:38:51 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/autocomp.h"

/*
** Built list if not exist. add elem in a existing list.
** hidden files are ignored if patern does not begin with '.'.
*/

static void		do_list(t_stream *stream, struct dirent *file, char *dir)
{
	size_t		data_size;
	struct stat	buf;
	char		*tmp;

	tmp = ft_strslashjoin(dir, file->d_name);
	data_size = 0;
	if (lstat(tmp, &buf) >= 0)
		data_size = (buf.st_mode & ~1);
	ft_freegiveone((void**)&tmp);
	if ((file->d_name[0] == '.' && COMP_BEGIN[0] == '.'
		&& ft_strcmp(file->d_name, ".")
		&& ft_strcmp(file->d_name, "..")) || file->d_name[0] != '.')
	{
		if (!COMP_BEGIN_LIST)
			COMP_BEGIN_LIST = ft_lstnew((S_ISDIR(data_size)) ?
				ft_strjoin(file->d_name, "/") :
					ft_strdup(file->d_name), data_size);
		else
			ft_list_push_back(&(COMP_BEGIN_LIST),
				ft_lstnew((S_ISDIR(data_size)) ? ft_strjoin(file->d_name, "/") :
					ft_strdup(file->d_name), data_size));
		get_pad(stream, file->d_name);
	}
}

/*
** Set needle for comaraison with open repertory. Can be NULL or match previous
** user defined pattern.
*/

void			set_comp(char *str, char **comp, size_t *len_comp,
					t_stream *stream)
{
	char *tmp;

	if (!COMP_MODE || COMP_MODE == 1)
		*comp = NULL;
	else if (!(*comp = ft_strrchr(str, '/')))
		*comp = ft_strdup(str);
	else
	{
		*comp = ft_strdup(++(*comp));
		tmp = COMP_BEGIN;
		COMP_BEGIN = ft_strdup(*comp);
		ft_freegiveone((void**)&tmp);
	}
	*len_comp = (!COMP_MODE || COMP_MODE == 1) ? 0 : ft_strlen(*comp);
}

/*
** Call set_comp, and set repertory to search. Can be:
** 1. PATH, 2. Current repertory, 3. Specified file in command.
*/

char			**set_dir(char *str, t_stream *stream, char **comp,
					size_t *len_comp)
{
	char	**dir;
	char	*tmp;
	char	*path;

	path = ft_strdup(str);
	set_comp(str, comp, len_comp, stream);
	if (COMP_MODE % 2)
		dir = ft_getenvtab("PATH", stream->config->env);
	else
	{
		if (!COMP_MODE || COMP_MODE == 1)
			tmp = getcwd(NULL, 0);
		else if (ft_strlen(path) == *len_comp)
			tmp = getcwd(NULL, 0);
		else
			tmp = ft_strsub(path, 0, (ft_strlen(path) - *len_comp));
		dir = ft_strsplit(tmp, ' ');
		free(tmp);
	}
	ft_freegiveone((void**)&path);
	return (dir);
}

/*
** Call set_dir. Built list depending on open directory(ies)
*/

void			build_list(char *str, t_stream *stream)
{
	DIR				*directory;
	struct dirent	*file;
	size_t			len_comp;
	char			**dir;
	char			*comp;

	dir = set_dir(str, stream, &comp, &len_comp);
	COMP_KILL = dir;
	while (*dir)
	{
		if ((directory = opendir(*dir)))
		{
			while ((file = readdir(directory)))
				if (!comp || !*comp)
					do_list(stream, file, *dir);
				else if (!ft_strncmp(COMP_BEGIN, file->d_name, len_comp))
					do_list(stream, file, *dir);
			closedir(directory);
		}
		ft_freegiveone((void **)&(*dir));
		dir++;
	}
	get_size_list(stream);
	ft_freegiveone((void**)&COMP_KILL);
	ft_freegiveone((void**)&comp);
}
