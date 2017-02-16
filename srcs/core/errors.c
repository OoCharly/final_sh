/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:54 by tboos             #+#    #+#             */
/*   Updated: 2017/02/16 19:03:18 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Returns name of file if an error occured.
*/

char		*ft_shname_or_file(char *name)
{
	static char	*errn = SHNAME;

	if (name)
		errn = name;
	return (errn);
}

static void	ft_last_exit_fail(int mode)
{
	t_stream	*stream;

	ft_status(1);
	stream = ft_save_stream(NULL);
	if (ft_script_line(0) && EEXIT & mode)
		ft_shell_exit(stream->config);
	if (stream && stream->config)
		stream->config->last_exit = 3;
}

int			ft_error(char *name, char *other, char *mess, int mode)
{
	if (mode & FCR_ERROR)
		ft_putchar_fd('\n', 2);
	if (name)
	{
		if (ft_strcmp(name, SHNAME))
			ft_putstr_fd(name, 2);
		else
			ft_putstr_fd(ft_shname_or_file(NULL), 2);
		ft_putstr_fd(": ", 2);
	}
	if (ft_script_line(0) && !ft_strcmp(SHNAME, name))
		FT_PUTSTRFD("ligne ", ft_st_itoa((int)ft_script_line(0)), ": ", 2);
	if (other)
	{
		ft_putstr_fd(other, 2);
		ft_putstr_fd(": ", 2);
	}
	if (mess)
		ft_putstr_fd(mess, 2);
	if (mode & CR_ERROR)
		ft_putchar_fd('\n', 2);
	ft_last_exit_fail(mode);
	return (true);
}

int			ft_initerror(t_config *config)
{
	ft_error(SHNAME, NULL, "init error", CR_ERROR);
	ft_shell_exit(config);
	return (1);
}
