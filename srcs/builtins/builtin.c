/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:16:34 by tboos             #+#    #+#             */
/*   Updated: 2017/02/22 11:43:21 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pwd(char **argv, t_config *config)
{
	char	buf[_POSIX_PATH_MAX];

	if (argv[1] && (argv[1][0] != '-' || argv[2]))
		ft_error("pwd", NULL, "too many arguments", CR_ERROR);
	else if (argv[1] && (argv[1][1] != 'L' && argv[1][1] != 'P'))
		ft_error("pwd", "unknown flag(s)", argv[1], CR_ERROR);
	else if (argv[1] && argv[1][1] == 'P')
	{
		if (!getcwd(buf, _POSIX_PATH_MAX))
			ft_error("pwd", NULL, "broken getcwd", CR_ERROR);
		else
			ft_putendl(buf);
	}
	else
		ft_putendl(config->pwd);
}

static int	ft_node_jobs(char **argv, t_config *config)
{
	if (!ft_strcmp(argv[0], "jobs"))
		ft_jobs(argv, config);
	else if (argv[0][0] == '%' || !ft_strcmp(argv[0], "fg")
			|| !ft_strcmp(argv[0], "bg"))
		ft_fgbg(argv, config, !ft_strcmp(argv[0], "bg") ? JOBS_BG : JOBS_FG);
	else
		return (0);
	return (1);
}

static void	ft_builtin_exit(char **argv, t_config *config)
{
	int		status;
	char	*p;

	p = argv[1];
	if (p)
	{
		status = ft_atoi(p);
		while (*p)
			if (!ft_isdigit(*(p++)))
				status = 255;
		ft_status(status);
		config->last_exit = status;
	}
	ft_status(config->last_exit);
	ft_shell_exit(config);
}

/*
**Returns 1 if argument is a builtin, in this case launch the appropriate
**function, otherwise return 0.
*/

int			ft_is_no_fork_builtin(char **argv, t_config *config)
{
	if (!ft_strcmp(argv[0], "exit"))
		ft_builtin_exit(argv, config);
	else if (!ft_strcmp(argv[0], "exitfather"))
		ft_kill_father(config);
	else if (ft_node_jobs(argv, config))
		;
	else if (!ft_strcmp(argv[0], "unsetenv"))
		ft_unsetenv(argv, config);
	else if (!ft_strcmp(argv[0], "setenv"))
		ft_readysetenv(argv, config);
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset(argv, config);
	else if (!ft_strcmp(argv[0], "export"))
		ft_export(argv, config);
	else if (!ft_strcmp(argv[0], "cd"))
		ft_cd(argv, config);
	else if (!ft_strcmp(argv[0], "history"))
		ft_history(argv, config);
	else
		return (0);
	config->last_exit = ft_status(0);
	return (1);
}

int			ft_builtin(char **argv, t_config *config)
{
	if (!ft_strcmp(argv[0], "pwd"))
		ft_pwd(argv, config);
	else if (!ft_strcmp(argv[0], "echo"))
		ft_echo(argv);
	else if (!ft_strcmp(argv[0], "env"))
		ft_env(argv, config);
	else
		return (0);
	config->last_exit = ft_status(0);
	return (1);
}
