#include "minishell.h"

/*
**Copies the current terminal attributes in config->termios and
**config->termios_backup. Changes the control mode in non canonical and stop
**echo of input characters. Defines a minimun of zero characters for
**noncanonical read. No defines a timeout for noncanonical read.
*/

int	ft_init_term(t_config *config)
{
	if (tcgetattr(STDIN_FILENO, &(config->termios_backup)) == -1
		|| !ft_memcpy(&(config->termios), &(config->termios_backup),
		sizeof(t_termios)))
		return (1 ^ ft_error(SHNAME, NULL, TERM_ERR, CR_ERROR));
	config->termios.c_lflag &= ~(ICANON | ECHO);
	config->termios.c_cc[VMIN] = 0;
	config->termios.c_cc[VTIME] = 1;
	return (true);
}

/*
**For the first call of function gets terminal attributes and Changes
**config->termios. If mode exists, modification of term attributes occurs after
**all output written to STDIN_FILENO has been transmitted. If mode doesn't
**exists, modification are set immediately.
*/

void	ft_termios_handle(t_config *config, int mode)
{
	static char		state = 0;

	if (!state && ft_init_term(config))
		state = 1;
	if (mode && state
		&& (tcsetattr(STDIN_FILENO, TCSADRAIN, &(config->termios)) == -1))
		ft_error(SHNAME, NULL, TERM_ERR, CR_ERROR);
	else if (!mode && state
		&& (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &(config->termios_backup))))
		ft_error(SHNAME, NULL, RESET_TERM_ERR, CR_ERROR);
	return ;
}


