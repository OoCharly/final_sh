/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:09:33 by jmunoz            #+#    #+#             */
/*   Updated: 2016/12/14 18:11:32 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Save once and  return list with valid files pathnames.
*/

static t_list	**ft_save_list(t_list **begin, char clear)
{
	static t_list **save = NULL;

	if (clear == 1)
		save = NULL;
	else if (!save)
		save = begin;
	return (save);
}

/*
** For one directory, check if each file fill the glob, append it to the saved
** path if ok. Discard "." and ".." and hidden files if not explicitely
** mentionned in glob. Call ft_glob with next path section in glob.
*/

static void		ft_check_file(char *file, char *glob, char *buf, int end)
{
	DIR		*dir;

	if (!ft_strcmp(file, ".") && !ft_strncmp(glob, "**/", 3))
	{
		if (glob[3])
			ft_glob((dir = opendir((!*buf) ? "." : buf)), buf,
					(glob + ft_strlenc(glob, '/') + 1));
		else
			ft_glob((dir = opendir((!*buf) ? "." : buf)), buf, (glob + 1));
		closedir(dir);
	}
	if (ft_match(glob, file) && ((ft_strcmp(file, ".") && ft_strcmp(file, "..")
	&& (*(file) != '.' || ft_match(".*", glob))) || (ft_match(".", glob) &&
	!ft_strcmp(file, ".")) || (ft_match("..", glob) && !ft_strcmp(file, ".."))))
	{
		if (ft_strcat(buf, file) && ft_strncmp(glob, "**/", 3))
			ft_glob((dir = opendir(buf)), buf, (glob + ft_strlenc(glob, '/')));
		else
			ft_glob((dir = opendir(buf)), ft_strcat(buf, "/"), glob);
		if (dir)
			closedir(dir);
		ft_bzero(&buf[end], (255 - end));
	}
}

/*
** Recursive function. If glob comes at a end, add the pathname to the list.
** if *glob is /, append it to the pathname and restart function. If it comes to
** a valid path section in glob, check the files that might be valid.
*/

void			ft_glob(DIR *dir, char *path, char *glob)
{
	char			buf[256];
	struct dirent	*file;
	int				end;
	t_list			**begin;

	begin = ft_save_list(NULL, 0);
	end = ft_strlen(ft_strcpy(buf, path));
	if (!*glob)
		ft_list_push_back(begin, ft_lstnew(ft_strdup(buf), 0));
	if (dir && *glob == '/')
		ft_glob(dir, ft_strcat(buf, "/"), ++glob);
	else if (dir)
		while ((file = readdir(dir)))
			ft_check_file(file->d_name, glob, buf, end);
}

/*
** Init list. Launch ft_glob either in absolute or relative mode. Transfer list
** result into a string.
*/

char			*ft_launch_glob(char *str)
{
	DIR		*stream;
	t_list	*begin;
	t_list	*tmp;
	char	*tot;

	begin = NULL;
	tot = NULL;
	ft_save_list(&begin, 0);
	if (!(stream = (*str == '/') ? opendir("/") : opendir(".")))
		return (NULL);
	ft_glob(stream, NULL, (char*)str);
	closedir(stream);
	if (begin && (tot = ft_strnew(ft_size_list(begin))))
		while (begin)
		{
			//ft_strcat(ft_strcat(tot, begin->data), "\n");
			tot[ft_strlen(ft_strcat(tot, begin->data))] = -1;
			tmp = begin;
			begin = begin->next;
			ft_lstdelone(&tmp, &ft_list_free_data);
		}
	ft_save_list(NULL, 1);
	return (tot);
}
