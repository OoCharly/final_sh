#include "minishell.h"

void	ft_scripting(int fd, t_config *config)
{
	char		*l;
	char		*command;
	char		*test;

	ft_script_line(-1);
	l = NULL;
	command = NULL;
	while ((get_next_line(fd, &l)) > 0 && ft_script_line(1))
	{
		if (!(command = command ? ft_strchrjoin(command, '\n', l)
			: ft_strdup(l)) && (command = l)
			&& ft_error(SHNAME, "malloc error", NULL, 1 | 4 | 8))
			break ;
		test = command;
		if (!(test = ft_matchchr(&test)))
		{
			config->command = command;
			ft_run_command(config);
			ft_freegiveone((void**)&config->command);
			command = NULL;
		}
		ft_freegiveone((void**)&l);
	}
	ft_freegiveone((void**)&command);
	get_next_line(-1, NULL);
}
/*
		while (get_next_line(0, &config->command) > 0 && ft_script_line(1))
		{
			test = config->command;
			if ((test = ft_matchchr(&test)))
				ft_error(SHNAME, PARSE_ERR, ft_qerr(test), 1 | SERROR | EEXIT);
			else
				ft_run_command(config);
			ft_freegiveone((void**)&config->command);
		}
		get_next_line(-1, NULL);
	}
*/
//void	ft_scripting(int fd, t_config *config)
//{
//}
