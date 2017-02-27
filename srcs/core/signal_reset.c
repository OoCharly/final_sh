/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 14:50:11 by rbaran            #+#    #+#             */
/*   Updated: 2017/02/01 14:54:14 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_reset(void)
{
	if (SIG_ERR == signal(SIGINT, SIG_DFL))
		ft_status(1);
	if (SIG_ERR == signal(SIGTSTP, SIG_DFL))
		ft_status(1);
	if (SIG_ERR == signal(SIGTTOU, SIG_DFL))
		ft_status(1);
	if (SIG_ERR == signal(SIGTTIN, SIG_DFL))
		ft_status(1);
	if (SIG_ERR == signal(SIGCHLD, SIG_DFL))
		ft_status(1);
}
