/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_signals.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 19:54:02 by rbaran            #+#    #+#             */
/*   Updated: 2017/01/12 11:10:38 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_set_suphandlers(void)
{
	if (SIG_ERR == signal(SIGQUIT, &ft_exit_supervisor)
		&& ft_error(SHNAME, "supervisor", "signal set", CR_ERROR))
		return (0);
	if (SIG_ERR == signal(SIGTSTP, SIG_DFL)
		&& ft_error(SHNAME, "supervisor", "signal set", CR_ERROR))
		return (0);
	if (SIG_ERR == signal(SIGSTOP, SIG_DFL)
		&& ft_error(SHNAME, "supervisor", "signal set", CR_ERROR))
		return (0);
	if (SIG_ERR == signal(SIGINT, SIG_IGN)
		&& ft_error(SHNAME, "supervisor", "signal set", CR_ERROR))
		return (0);
	return (1);
}
