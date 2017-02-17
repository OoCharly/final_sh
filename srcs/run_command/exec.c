/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:20:26 by tboos             #+#    #+#             */
/*   Updated: 2017/02/17 17:12:22 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_path_handle(char **argv, t_config *config)
{
	char	*path;

	path = NULL;
	if (!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "echo")
		|| !ft_strcmp(argv[0], "env") || !ft_strcmp(argv[0], "printenv"))
		return (argv[0]);
	if (config->env &&
		ft_strcmp(config->last_hash, ft_strtabfindstart(config->env, "PATH=")))
		ft_pathtohash(config);
	if (ft_return_binpath(config, argv[0], &path))
	{
		path = NULL;
		ft_pathtohash(config);
		ft_return_binpath(config, argv[0], &path);
		path = (path) ? path : argv[0];
	}
	if (!ft_access_exec(path, argv, config))
		return (NULL);
	return (path);
}

void		ft_execve(char *path, char **argv, char **env)
{
	static char	*rearg[3] = {"./21sh", NULL, NULL};

	if ((-1 == execve(path, argv, env)) && (rearg[1] = path) &&
			(-1 == execve(SHNAME, rearg, env)))
	{
		if (ft_strtablen(argv) + ft_strtablen(env) > _POSIX_ARG_MAX)
			ft_error(SHNAME, "argument list too long", argv[0], CR_ERROR);
		else
			ft_error(SHNAME, "exec", "execve error", CR_ERROR);
	}
}

void		ft_launch_process(char *path, char **argv, t_config *config)
{
	if (ft_builtin(argv, config))
		return ;
	ft_execve(path, argv, config->env);
}

void		ft_kill_father(t_config *config)
{
	ft_free_config(config);
	if (-1 == kill(getppid(), SIGKILL))
		ft_error(SHNAME, "SORRY", JEDI_ERR, CR_ERROR);
	exit(0);
}
