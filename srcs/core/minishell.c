/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2016/12/19 17:02:01 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_gotonextline(t_stream *stream)
{
	ft_putchar('\n');
	stream->tput = "le";
	ft_tputs(stream);
	ft_tputs(stream);
}

/*
** Strip a string from " ' '\' with the correct rules
*/

int			ft_cleancmd(char *str)
{
	char	tok;
	char	*mem;

	mem = str;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			tok = *str;
			ft_memmove(str, str + 1, ft_strlen(str));
			while (*str && *str != tok)
			{
				if (*str == '\\' && tok == '"' && *(str + 1) == tok)
					ft_memmove(str, str + 1, ft_strlen(str));
				str++;
			}
			ft_memmove(str, str + 1, ft_strlen(str));
		}
		else if (*(str++) == '\\')
			ft_memmove(str - 1, str, ft_strlen(str) + 1);
		else
			str++;
	}
	return (1);
}

void		ft_print_list(t_list *elem)
{
	if (!elem->data_size)
	{
		ft_putstr("\nargv :\n");
		if (elem->data)
			ft_putstrtab((char **)(elem->data), '\n');
		ft_putchar('\n');
	}
	else if (elem->data_size == SSHELL)
	{
		ft_putstr("\nSSHELL :\n");
		ft_lstiter((t_list *)elem->data, ft_print_list);
	}
	else if (elem->data_size == OP)
		FT_PUTSTRFD("\nop :\n", (char*)elem->data, "\n", 1);
	else if (elem->data_size == JOB)
		ft_print_jobs(elem->data, NULL);
	else if (elem->data_size == PIPE)
	{
		ft_putstr("\npipe :\n");
		ft_putnbr(((int*)elem->data)[0]);
		ft_putnbr(((int*)elem->data)[1]);
		ft_putchar('\n');
	}
}

void		ft_run_command(t_config *config)
{
	config->shell_state = RUNNING_COMMAND;
	if ((config->chimera = ft_lexer(config->command)))
	{
		if (!ft_quote(config->chimera, config)
				|| !ft_insert_loop(config->chimera)
				|| !ft_herringbone(config->chimera, config))
			ft_freelist(&config->chimera);
		else
		{
			ft_parse(config);
		}
	}
	ft_freegiveone((void**)&config->command);
}

/*
**If an interuption signal is caught, frees config structure and exits.
**Memorizes adress of stream in a static variable.
*/

void		ft_minishell(t_config *config)
{
	int		fd;

	fd = 1;
	if ((ft_signal(SIGNAL_SET
		&& ft_error(SHNAME, "unable to set signal", "I quit", 1 | SERROR)))
			|| (!isatty(1) && !(fd = 0) && !isatty(0)
				&& ft_error(SHNAME, "unable write and read from the same fd",
					"I quit", 1 | SERROR)))
		ft_shell_exit(config);
	config->shell_state = SCANNING_COMMAND;
	while (1)
		if ((config->command = ft_streamscan(config, ft_save_stream(NULL), fd)))
		{
			ft_run_command(config);
			if (config->shell_state != RUNNING_COMMAND)
				ft_gotonextline(ft_save_stream(NULL));
			config->shell_state = SCANNING_COMMAND;
		}
}
