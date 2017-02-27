/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:21:35 by tboos             #+#    #+#             */
/*   Updated: 2017/02/27 13:29:25 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_default_env(t_config *config)
{
	t_passwd	*passwd;
	char		*tmp;

	if (!(passwd = getpwuid(getuid()))
	|| !(tmp = getcwd(NULL, 0))
	|| (!config->env && !(config->env = (char**)ft_memalloc(sizeof(char*)))))
		return (false);
	ft_setenv("PWD", tmp, config);
	ft_freegiveone((void**)&tmp);
	if (!ft_getenv("HOME", config->env))
		ft_setenv("HOME", passwd->pw_dir, config);
	if (!ft_getenv("USER", config->env))
		ft_setenv("USER", passwd->pw_name, config);
	if (!ft_getenv("LSCOLORS", config->env))
		ft_setenv("LSCOLORS", DLSCOLORS, config);
	return (true);
}

void	ft_setenv(char *n, char *val, t_config *config)
{
	int		i;
	char	**f;
	char	*mem;

	f = config->env;
	if (((i = ft_igetenv(n, f)) >= 0
		&& (mem = f[i])
		&& ((val && !(f[i] = ft_strfjoin(ft_strjoin(n, "="), val, 1)))
		|| (!val && !(f[i] = ft_strjoin(n, "="))))
		&& (f[i] = mem)))
		ft_error(SHNAME, "error while setenv for", n, CR_ERROR);
	else if (i >= 0 && !ft_strcmp(n, "PWD"))
		ft_setenv("OLDPWD", mem + 4, config);
	else if (i < 0 && ((val && !(mem = ft_strfjoin(ft_strjoin(n, "="), val, 1)))
		|| (!val && !(mem = ft_strjoin(n, "=")))))
		ft_error(SHNAME, "malloc error during setenv for", n, CR_ERROR);
	else if (i < 0 && !(config->env = ft_strtabadd(config->env, mem))
		&& ft_freegiveone((void **)&mem) && (config->env = f))
		ft_error(SHNAME, "malloc error during setenv for", n, CR_ERROR);
	else if (f && config->env && f != config->env)
		FREE((void**)&f);
	if (config->shell_state != RUNNING_SON && n && !ft_strcmp("PATH", n))
		ft_pathtohash(config);
	(i >= 0) ? ft_freegiveone((void**)&(mem)) : 1;
	ft_list_remove_if(&config->variables, N, &var_name_cmp, &ft_list_free_elem);
}

void	ft_readysetenv(char **argv, t_config *config)
{
	int		i;
	char	*t;

	i = 0;
	while (argv[++i])
	{
		if ((t = ft_strchr(argv[i], '=')))
		{
			*t = '\0';
			ft_setenv(argv[i], t + 1, config);
		}
		else
			ft_setenv(argv[i], NULL, config);
	}
}

void	ft_unsetenv(char **argv, t_config *config)
{
	int		i;
	int		n;
	char	**cp;

	i = 0;
	cp = config->env;
	while (argv[++i])
	{
		if ((n = ft_igetenv(argv[i], cp)) >= 0)
		{
			FREE((void**)&cp[n]);
			cp[n] = cp[n + 1];
			while (cp[++n])
				cp[n] = cp[n + 1];
			if (config->shell_state != RUNNING_SON
				&& !ft_strncmp("PATH", argv[i], 4) && ft_strlen(argv[i]) == 4)
				ft_pathtohash(config);
		}
	}
}
