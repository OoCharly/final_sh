/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:37:57 by tboos             #+#    #+#             */
/*   Updated: 2017/02/27 16:08:33 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_clean_path(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '/' && ((str[i + 1] == '.' && (str[i + 2] == '/'
				|| !str[i + 2])) || (str[i + 1] == '/')))
			ft_strcpy(str + i, str + i + ((str[i + 1] == '/') ? 1 : 2));
		else if (str[i] == '/' && str[i + 1] == '.' && str[i + 2] == '.'
				&& (str[i + 3] == 0 || str[i + 3] =='/')
				&& i - 2 > 0 && str[i - 1] != '.' && str[i - 2] != '.')
		{
			while (--i != 0 && str[i] != '/')
				;
			ft_strcpy(str + i + 1, ft_strchr(str + i + 1, '/') + 3);
		}
		else
			i++;
	}
	while (*str == '/' && *(str + 1) == '.'
			&& ((*(str + 2) == '.' && (*(str + 3) == '/' || *(str + 3) == 0))
			|| (*(str + 2) == 0)))
		ft_memmove(str + 1, str + (*(str + 2) ? 4 : 2), ft_strlen(str + 2) + 2);
	while (*str == '/' && *(str + 1) == '/')
		ft_strcpy(str, str + 1);
}

void		ft_update_prompt(t_config *config)
{
	char	*pwd;

	ft_freegiveone((void**)&(config->pwd));
	if (!(pwd = ft_strdup(ft_getenv("PWD", config->env)))
			|| ((pwd[0] == 0) && ft_freegiveone((void**)&pwd)))
	{
		if (!(pwd = getcwd(NULL, 0)))
		{
			ft_error(SHNAME, NULL, PATH_MAX_ERR, CR_ERROR | SERROR);
			config->pwd_subrep = "???";
			config->prompt_len = 9;
			return ;
		}
		else
			ft_setenv("PWD", pwd, config);
	}
	config->pwd = pwd;
	config->pwd_subrep = (!pwd[1] ? pwd : ft_strrchr(pwd, '/') + 1);
	config->prompt_len = ft_strlen(config->pwd_subrep) + 6;
}

static void	ft_path_follow(char *path, t_config *config, int nosymlink)
{
	struct stat	buf;
	char		*err;

	if (nosymlink == 1)
		path = ft_resolve_symlink(path);
	ft_clean_path(path);
	if ((err = &path[ft_strlen(path) - 1]) && (*err == '/') && (err != path))
		*err = 0;
	if (((err = "no directory or file named") && -1 == access(path, F_OK))
			|| ((err = "access denied") && -1 == stat(path, &buf))
			|| ((err = "not a directory") && !S_ISDIR(buf.st_mode))
			|| ((err = "permission denied") && -1 == access(path, X_OK))
			|| (err = NULL))
		ft_error("cd", err, path, CR_ERROR);
	else if (!chdir(path))
	{
		ft_setenv("PWD", (nosymlink) ? (err = getcwd(NULL, 0)) : path, config);
		ft_update_prompt(config);
		FREE((void**)&err);
		FREE((void**)&path);
		return ;
	}
	else
		ft_error(SHNAME, "failed moving to directory", path, CR_ERROR);
	FREE((void**)&path);
}

static int	cd_option(char *arg, char *path, t_config *config)
{
	if (!arg[1])
	{
		if (!(path = ft_strdup(ft_getenv("OLDPWD", config->env)))
				|| (!*path && FREE((void**)&path)))
			ft_error(SHNAME, "cd", "OLDPWD not set", CR_ERROR);
		else
		{
			ft_putendl(path);
			ft_path_follow(path, config, 0);
		}
		return (-1);
	}
	else if (arg[1] == 'P' && FREE((void**)&(config->pwd)))
	{
		config->pwd = getcwd(NULL, 0);
		return (1);
	}
	else if (arg[1] != 'L')
	{
		ft_error("cd", arg, "invalid option", CR_ERROR);
		ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
		return (-1);
	}
	return (0);
}

void		ft_cd(char **argv, t_config *config)
{
	char	*path;
	int		i;
	int		nosymlink;

	path = NULL;
	i = (ft_strcmp(argv[0], "cd") ? 0 : 1);
	nosymlink = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		nosymlink = cd_option(argv[i], path, config);
		if (nosymlink != -1)
			i++;
		else
			return ;
	}
	if (!path && !argv[i] && (((path = ft_getenv("HOME", config->env))
				&& *path) || !ft_error(SHNAME, "cd", "HOME not set", CR_ERROR)))
		path = ft_strdup(path);
	else if (argv[i] && argv[i][0] == '/')
		path = ft_strdup(argv[i]);
	else if (argv[i] && (path = config->pwd))
		path = ft_strslashjoin(path, argv[i]);
	if (path && *path)
		ft_path_follow(path, config, nosymlink);
}
