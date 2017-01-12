/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:19:41 by rbaran            #+#    #+#             */
/*   Updated: 2017/01/12 16:22:29 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_manag(t_list **process, t_list *tmp)
{
	if (!process || !*process)
	{
		setpgid(*((pid_t*)tmp->data), *((pid_t*)tmp->data));
		tcsetpgrp(0, *((pid_t*)tmp->data));
	}
	else
		setpgid(*((pid_t*)tmp->data), *((pid_t*)(*process)->data));
	ft_list_push_back(process, tmp);
}
