/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:19:41 by rbaran            #+#    #+#             */
/*   Updated: 2017/01/26 16:23:52 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_manag(t_list **process, t_list *tmp, t_config *config)
{
	if (!process || !*process)
	{
		setpgid(*((pid_t*)tmp->data), *((pid_t*)tmp->data));
		if (config->dot_sequence != 'b')
			tcsetpgrp(0, *((pid_t*)tmp->data));
		else if (!config->script_state)
			signal(SIGTTOU, SIG_DFL);
	}
	else
		setpgid(*((pid_t*)tmp->data), *((pid_t*)(*process)->data));
	ft_list_push_back(process, tmp);
}
