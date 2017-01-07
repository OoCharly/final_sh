/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 18:05:02 by rbaran            #+#    #+#             */
/*   Updated: 2017/01/07 01:00:27 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		ft_exit_supervisor(int signum)
{
	ft_shell_exit(ft_save_config(NULL));
}

pid_t		ft_supervisor(t_list **process, int mode, t_config *config)
{
	pid_t	pid;

	if ((pid = fork()) == -1
		&& ft_error(SHNAME, "supervisor", "fork error", CR_ERROR))
		return (0);
	if (pid == 0)
		if (!ft_set_handlers())
			ft_shell_exit(config);
	else if (pid > 0 && mod == STOP)
		kill(pid, SIGSTOP);
	return (pid);
}
