/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:09:33 by jmunoz            #+#    #+#             */
/*   Updated: 2017/02/17 17:53:16 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_loop(int i) 
{
	static size_t save = 0;

	if (i < 0)
		save = 0;
	else if (i > 0)
		save += i;
	return (save);
}

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
	if (ft_match(glob, file, 0) && ((ft_strcmp(file, ".")
	&& ft_strcmp(file, "..") && (*(file) != '.' || ft_match(".*", glob, 0)))
	|| (ft_match(".", glob, 0) && !ft_strcmp(file, "."))
	|| (ft_match("..", glob, 0) && !ft_strcmp(file, ".."))))
	{
		if (ft_strcat(buf, file) && ft_strncmp(glob, "**/", 3))
			ft_glob((dir = opendir(buf)), buf, (glob + ft_strlenc(glob, '/')));
		else
			ft_glob((dir = opendir(buf)), ft_strcat(buf, "/"), glob);
		if (dir)
			closedir(dir);
		ft_bzero(&buf[end], _POSIX_PATH_MAX - end);
	}
}

/*
** Recursive function. If glob comes at a end, add the pathname to the list.
** if *glob is /, append it to the pathname and restart function. If it comes to
** a valid path section in glob, check the files that might be valid.
*/

void			ft_glob(DIR *dir, char *path, char *glob)
{
	char			buf[_POSIX_PATH_MAX + 1];
	struct dirent	*file;
	int				end;
	t_list			**begin;

	begin = ft_save_list(NULL, 0);
	end = ft_strlen(ft_strcpy(buf, path));
	if (!*glob && ft_count_loop(1))
		ft_list_push_back(begin, ft_lstnew(ft_strdup(buf), 0));
	if (dir && *glob == '/')
		ft_glob(dir, ft_strcat(buf, "/"), ++glob);
	else if (dir)
		while ((file = readdir(dir))) 
		{
			if (ft_count_loop(0) > GLOB_LIST_LIMIT)
				break;
			ft_check_file(file->d_name, glob, buf, end);
		}
}

/*
** Init list. Launch ft_glob either in absolute or relative mode. Transfer list
** result into a string.
*/

char			**ft_launch_glob(char *str)
{
	DIR		*current_dir;
	t_list	*begin;
	t_list	*tmp;
	char	**result;

	begin = NULL;
	result = NULL;
	ft_save_list(&begin, 0);
	if (!(current_dir = (*str == '/') ? opendir("/") : opendir(".")))
		return (NULL);
	ft_glob(current_dir, NULL, (char*)str);
	ft_count_loop(-1);
	closedir(current_dir);
	while (begin)
	{
		result = ft_strtabadd_free(result, begin->data);
		tmp = begin;
		begin = begin->next;
		ft_lstdelone(&tmp, NULL);
	}
	ft_save_list(NULL, 1);
	return (result);
}
