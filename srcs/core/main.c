/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:44:08 by tboos             #+#    #+#             */
/*   Updated: 2017/02/15 19:07:26 by tboos            ###   ########.fr       */
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
	char		*c;
	char		*home;

	if ((!(home = ft_getenv("HOME", config->env)))
		|| !(c = ft_strslashjoin(home, av)))
		return (ft_initerror(config));
	if (!(config->hloc = ft_strrchr(c, '/')) && ft_freegiveone((void**)&c))
		return (ft_initerror(config));
	config->hloc[0] = '\0';
	if (!(config->hloc = ft_strjoin(c, "history.bck"))
			&& ft_freegiveone((void**)&c))
		return (ft_initerror(config));
	ft_freegiveone((void**)&c);
	return (0);
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
	if (!env || !env[0] || !(config.env = ft_strtabdup(env))
			|| !ft_pathtohash(&config))
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
