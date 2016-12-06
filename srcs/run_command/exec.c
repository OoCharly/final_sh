/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:20:26 by tboos             #+#    #+#             */
/*   Updated: 2016/11/14 09:03:33 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_path_handle(char **argv, t_config *config)
{
	char	*path;

	if (!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "echo")
		|| !ft_strcmp(argv[0], "env") || !ft_strcmp(argv[0], "printenv"))
		return (argv[0]);
	if ((path = ft_return_binpath(config, argv[0])))
		;
	else
		path = argv[0];
	if (!ft_access_exec(path, argv, config))
		return (NULL);
	return (path);
}

void		ft_execve(char *path, char **argv, char **env)
{
	if (-1 == execve(path, argv, env))
		ft_error(SHNAME, "exec", "execve error", CR_ERROR);
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
