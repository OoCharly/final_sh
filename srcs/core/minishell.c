/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:43:47 by tboos             #+#    #+#             */
/*   Updated: 2017/02/27 19:02:44 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_print_list(t_list *elem)
{
	if (elem->data_size == VAR)
	{
		ft_putstr(((t_var*)elem->data)->name);
		if (((t_var*)elem->data)->type != VAR_FUN)
			ft_putchar('=');
		else
			ft_putstr("()\n");
		if (((t_var*)elem->data)->type != VAR_TAB)
			ft_putstr((char*)((t_var*)elem->data)->value);
		else
			ft_putstrtab((char**)((t_var*)elem->data)->value, '\n');
		ft_putchar('\n');
	}
	else if (!elem->data_size && elem->data)
		ft_putstrtab((char **)(elem->data), '\n');
	else if (elem->data_size == SSHELL)
		ft_lstiter((t_list *)elem->data, ft_print_list);
	else if (elem->data_size == OP)
		FT_PUTSTRFD("\nop :\n", (char*)elem->data, "\n", 1);
	else if (elem->data_size == JOB)
		ft_print_jobs(elem->data, NULL);
}

static int	ft_parse_keeper(t_list *chimera)
{
	int		op;

	op = 1;
	while (chimera)
	{
		if (!chimera->data_size || (chimera->data_size == 1
			&& (ft_strchr((char*)chimera->data, '<')
				|| (ft_strchr((char*)chimera->data, '>')))))
			op = 0;
		else if (chimera->data_size == SSHELL && (op == 0
			|| !ft_parse_keeper(chimera->data)) && ft_error(SHNAME,
			"parse error near", "(", CR_ERROR))
			return (0);
		else if (chimera->data_size == SSHELL)
			op = 0;
		else
			op = 1;
		chimera = chimera->next;
	}
	return (1);
}

void		ft_run_command(t_config *config)
{
	config->shell_state = RUNNING_COMMAND;
	ft_status(666);
	config->lexerlop = 0;
	if ((config->chimera = ft_lexer(config->command)))
	{
		if (!ft_parse_keeper(config->chimera))
			ft_freelist(&config->chimera);
		else if (!ft_herringbone(config->chimera, config))
			ft_freelist(&config->chimera);
		else
			ft_parse(config);
	}
	else
		config->last_exit = ft_status(0);
	ft_freegiveone((void**)&config->command);
	ft_freegiveone((void**)&config->free);
}

/*
**If an interuption signal is caught, frees config structure and exits.
**Memorizes adress of stream in a static variable.
*/

void		ft_minishell(t_config *config)
{
	int		fd;

	fd = 1;
	config->shell_pgid = getpgrp();
	if ((ft_signal(SIGNAL_SET
		&& ft_error(SHNAME, "unable to set signal", "I quit", 1 | SERROR)))
			|| (!isatty(1) && !(fd = 0) && !isatty(0)
				&& ft_error(SHNAME, "unable write and read from the same fd",
					"I quit", 1 | SERROR)))
		ft_shell_exit(config);
	config->shell_state = SCANNING_COMMAND;
	while (1)
	{
		if ((config->command = ft_streamscan(config, ft_save_stream(NULL), fd)))
		{
			ft_run_command(config);
			config->shell_state = SCANNING_COMMAND;
		}
	}
}
