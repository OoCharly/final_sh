/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 18:05:02 by rbaran            #+#    #+#             */
/*   Updated: 2017/01/11 15:59:16 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_setprocess(t_list **process, pid_t pgid)
{
	t_list	*head;

	head = process ? *process : NULL;
	while (head)
	{
		printf("%d\n", setpgid(*((pid_t*)(*process)->data), pgid));
		head = head->next;
	}
}

void			ft_exit_supervisor(int signum)
{
	signum = 0;
	ft_shell_exit(ft_save_config(NULL));
}

pid_t			ft_supervisor(t_list **process, int mod, t_config *config)
{
	pid_t	pid;

	if ((pid = fork()) == -1
		&& ft_error(SHNAME, "supervisor", "fork error", CR_ERROR))
		return (0);
	if (pid == 0)
	{
		if (!ft_set_suphandlers())
			ft_shell_exit(config);
		setpgid(0, getpid());
	}
	else if (pid > 0 && mod == STOP)
	{
		ft_setprocess(process, pid);
		kill(pid, SIGSTOP);
	}
	return (pid);
}
