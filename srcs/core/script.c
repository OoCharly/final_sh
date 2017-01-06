#include "minishell.h"

static char	*ft_set_test(char *current)
{
	static char	*test = NULL;
	char		*memo;

	memo = test;
	test = current;
	return (memo);
}

static void	ft_eof_error(int script_line)
{
	int			eof_line;
	char		*test;
	char		cha[2];

	cha[1] = 0;
	eof_line = ft_script_line(0);
	ft_script_line(-script_line);
	test= ft_set_test(NULL);
	ft_error(SHNAME, NULL, test + 2, 1 | 4);
	ft_script_line(-eof_line);
	cha[0] = *(test + 1);
	ft_error(SHNAME, UEOF_ERR, cha, 1 | 4 | EEXIT);
}

/*
**Returns line if an error occured.
*/

size_t		ft_script_line(int mode)
{
	static size_t	script_line = 0;

	if (mode == -1)
		script_line = 1;
	if (mode < -1)
		script_line = -mode;
	else if (mode)
		script_line += mode;
	return (script_line);
}

static char	*ft_scripting_inloop(char *command, char *l, t_config *config)
{
	char		*test;

	config->command = command;
	if (!(command = command ? ft_strchrjoin(command, '\n', l) : ft_strdup(l))
		&& ft_freegiveone((void**)&l)
		&& ft_error(SHNAME, NULL, "malloc error", 1 | 4 | 8))
		return (NULL);
	ft_freegiveone((void**)&config->command);
	test = command;
	if (!(test = ft_matchchr(&test)))
	{
		config->command = command;
		ft_run_command(config);
		ft_freegiveone((void**)&config->command);
		command = NULL;
		ft_set_test(NULL);
	}
	else
		ft_set_test(test);
	ft_freegiveone((void**)&l);
	return (command);
}

void		ft_scripting(int fd, t_config *config)
{
	char		*command;
	char		*test;
	char		*l;
	int			err_line;

	ft_script_line(-1);
	command = NULL;
	err_line = 0;
	while (!(l = NULL) && (get_next_line(fd, &l)) > 0)
	{
		ft_script_line(1);
		if ((command = ft_scripting_inloop(command, l, config)))
		{
			test = ft_set_test(NULL);
			if (test[0] == '0' && ft_error(SHNAME, test + 2, NULL, 1 | 4 | 8))
				break ;
			else if (!err_line)
				err_line = ft_script_line(0);
			ft_set_test(test);
		}
		else
			err_line = 0;
	}
	ft_freegiveone((void**)&command);
	if (err_line)
		ft_eof_error(err_line);
}
