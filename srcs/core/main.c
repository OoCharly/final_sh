/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:08 by tboos             #+#    #+#             */
/*   Updated: 2017/02/27 13:32:26 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_manage_files(int ac, char **av, t_config *config)
{
	int			fd;
	int			i;

	i = 0;
	while (++i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) < 0
				&& ft_error(SHNAME, "can't open input file", av[i], 1 | SERROR))
			return ;
		ft_shname_or_file(av[i]);
		ft_scripting(fd, config, NULL);
		close(fd);
		ft_shname_or_file(SHNAME);
	}
}

/*
**If stdin is a terminal, initializes termcaps and launch stream scan. Otherwise
**reads command on stdin and run command directly without stream scan. If the
**shell has a file in parameter, tries to opens and reads it.
*/

static void	ft_tricase(int ac, char **av, t_config *config)
{
	ft_signal(SIGNAL_SCRIPT);
	if (ac == 1 && isatty(0))
	{
		ft_termcaps_init(config);
		ft_minishell(config);
	}
	else if (ac == 1 && (config->heredoc = 2))
		ft_scripting(0, config, NULL);
	else if ((config->heredoc = 2))
		ft_manage_files(ac, av, config);
	ft_shell_exit(config);
}

static int	ft_history_loc_init(t_config *config, char *av)
{
	char		*home;

	(void)av;
	if (!(home = ft_getenv("HOME", config->env)) || home[0] == 0)
	{
		ft_error(SHNAME, "failed to load history", "HOME not set", CR_ERROR);
		if (!(home = getcwd(NULL, 0)))
			return (ft_initerror(config));
		home = ft_strfjoin(home, "/", 1);
	}
	else
		home = ft_strjoin(home, "/");
	if (home && (config->hloc = ft_strfjoin(home, ".history.bck", 1)))
		return (0);
	return (ft_initerror(config));
}

/*
**Copies environment in config.env, copies all binaries in config.binary.
**Copies pathname of current working directory in config.pwd. Increases the
**shell level.
*/

int			main(int ac, char **av, char **env)
{
	t_config	config;
	t_stream	stream;
	int			i;

	ft_bzero(&config, sizeof(t_config));
	config.env = ft_strtabdup(env);
	if (!ft_default_env(&config) || !ft_pathtohash(&config))
		return (ft_initerror(&config));
	ft_update_prompt(&config);
	if ((i = ft_strtabifindstart(env, "SHLVL")) != -1)
		ft_setenv("SHLVL", ft_st_itoa(ft_atoi(env[i] + 6) + 1), &config);
	if (ft_history_loc_init(&config, av[0]))
		return (1);
	ft_load_history(&config);
	ft_save_stream(&stream);
	ft_save_config(&config);
	stream.config = &config;
	ft_tricase(ac, av, &config);
	return (0);
}
