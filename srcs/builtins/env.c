/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:14:44 by rbaran            #+#    #+#             */
/*   Updated: 2017/01/04 12:30:48 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_printhelp(char c)
{
	if (c)
	{
		ft_putstr("env: illegal option -- ");
		ft_putchar(c);
		ft_putchar('\n');
	}
	ft_putendl("usage: env [-i] [-u name]");
	ft_putendl("\t[name=value ...] [utility [argument ...]]");
	return ;
}

static int	ft_parseparams(char **argv, int *param, t_config *config)
{
	char	*unset[3];
	int		i;

	unset[2] = NULL;
	i = 0;
	while (argv[++i] && argv[i][0] == '-')
	{
		if (argv[i][1] == 'h' || !ft_strcmp(argv[i], ENV_HELP))
			*param |= ENV_H;
		else if (argv[i][1] == 'i' || !ft_strcmp(argv[i], ENV_IGNORE))
			*param |= ENV_I;
		else if ((argv[i][1] == 'u' || !ft_strcmp(argv[i], ENV_UNSET))
				&& ++i)
		{
			unset[1] = argv[i];
			ft_unsetenv((char**)unset, config);
		}
		else
		{
			ft_printhelp(argv[i][1]);
			return (-1);
		}
	}
	return (i);
}

static void	ft_createenv(char **argv, t_config *config, int *i)
{
	char	*equal;

	while (argv[*i] && (equal = ft_strchr(argv[*i], '=')))
	{
		*equal = '\0';
		ft_setenv(argv[*i], equal + 1, config);
		(*i)++;
	}
}

static void	ft_printenv(char **env)
{
	if (!env)
		return ;
	ft_putstrtab(env, '\n');
	ft_putchar('\n');
}

void		ft_env(char **argv, t_config *config)
{
	int		param;
	char	*path;
	int		index;

	param = 0;
	if ((index = ft_parseparams(argv, &param, config)) < 0
			&& (config->last_exit = 1))
		return ;
	if (param & ENV_H)
		return (ft_printhelp(0));
	if (param & ENV_I)
	{
		ft_strtabfree(config->env);
		config->env = NULL;
	}
	ft_createenv(argv, config, &index);
	if (!argv[index])
		ft_printenv(config->env);
	if ((path = ft_path_handle(argv + index, config)))
		ft_launch_process(path, argv + index, config);
}
