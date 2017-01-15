/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:37:57 by tboos             #+#    #+#             */
/*   Updated: 2017/01/05 16:12:17 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pwd_error(t_config *config)
{
	ft_error(SHNAME, NULL, PATH_MAX_ERR, CR_ERROR | SERROR);
	config->pwd_subrep = "???";
	config->prompt_len = 9;
}

static void	ft_clean_path(char *path)
{
	int		i;

	i = 0;
	while (path && path[i])
	{
		if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '/')
			ft_strcpy(path + i, path + i + 2);
		else if (path[i] == '/' && path[i + 1] == '.' && path[i + 2] == '.'
			&& i - 2 > 0 && path[i - 1] != '.' && path[i - 2] != '.')
		{
			while (--i != 0 && path[i] != '/')
				;
			ft_strcpy(path + i + 1, ft_strchr(path + i + 1, '/') + 3);
		}
		else if (path[i] == '/' && path[i + 1] == '/')
			ft_memmove(path + i, path + i + 1, strlen(path + i));
		else
			i++;
	}
	if (path && i > 2 && path[i - 1] == '.' && path[i - 2] == '/')
		path[i - 1] = '\0';
	if (path && i && path[i - 1] == '/')
		path[i - 1] = '\0';
	if (*path == '/' && *(path + 1) == '.' && *(path + 2) == '.')
		*(path + 1) = '\0';
	if (!*path)
		*path = '/';
}

void		ft_update_prompt(t_config *config)
{
	char	buf[_POSIX_PATH_MAX];
	char	*pwd;

	ft_freegiveone((void**)&(config->pwd));
	if (!((pwd = ft_strtabfindstart(config->env, "PWD="))
		&& ft_strncpy(buf, pwd + 4, _POSIX_PATH_MAX)))
	{
		if (!getcwd(buf, _POSIX_PATH_MAX))
		{
			ft_pwd_error(config);
			return ;
		}
		ft_setenv("PWD", ft_strdup(buf), config);
	}
	if (!(pwd = ft_strdup(buf)))
		ft_pwd_error(config);
	else
	{
		config->pwd = pwd;
		config->pwd_subrep = (!pwd[1] ? pwd : ft_strrchr(pwd, '/') + 1);
		config->prompt_len = ft_strlen(config->pwd_subrep) + 6;
	}
}

static void	ft_path_follow(char *path, t_config *config)
{
	struct stat	buf;

	ft_clean_path(path);
	if (path[1] && !ft_access_dir(path))
		;
	else if (-1 == access(path, F_OK))
		ft_error(SHNAME, "no directory or file named", path, CR_ERROR);
	else if (-1 == stat(path, &buf))
		ft_error(SHNAME, "access denied", path, CR_ERROR);
	else if (!S_ISDIR(buf.st_mode))
		ft_error(SHNAME, "not a directory", path, CR_ERROR);
	else if (-1 == access(path, X_OK))
		ft_error(SHNAME, "permission denied", path, CR_ERROR);
	else if (!chdir(path))
	{
		ft_setenv("PWD", path, config);
		ft_update_prompt(config);
		return ;
	}
	else
		ft_error(SHNAME, "failed moving to directory", path, CR_ERROR);
	FREE((void**)&path);
}

void		ft_cd(char **argv, t_config *config)
{
	char	*path;
	int		i;

	path = NULL;
	if ((i = (ft_strcmp(argv[0], "cd") ? 0 : 1)) && ft_strtablen(argv) - i > 1
		&& ft_error(SHNAME, "cd", "too many arguments", CR_ERROR))
		return ;
	else if (!argv[i] && (path = ft_getenv("HOME", config->env)))
		path = ft_strdup(path);
	else if (argv[i] && argv[i][0] == '/')
		path = ft_strdup(argv[i]);
	else if (argv[i] && argv[i][0] == '~'
			&& (path = ft_getenv("HOME", config->env)))
		path = ft_strslashjoin(path,
				(ft_strlen(argv[i]) > 2 ? argv[i] + 2 : "."));
	else if (argv[i] && argv[i][0] == '-'
			&& (path = ft_strdup(ft_getenv("OLDPWD", config->env))))
		ft_putendl(path);
	else if (argv[i] && (path = config->pwd))
		path = ft_strslashjoin(path, argv[i]);
	if (path)
		ft_path_follow(path, config);
	else
		ft_error(SHNAME, "cd", "something is missing in env", CR_ERROR);
}
