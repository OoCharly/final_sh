/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 12:56:00 by tboos             #+#    #+#             */
/*   Updated: 2017/02/16 17:34:31 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_get_signalerr(int signum, char *err)
{
	if (signum == SIGSEGV)
		err = ERR_SEGV;
	else if (signum == SIGQUIT)
		err = ERR_QUIT;
	else if (signum == SIGILL)
		err = ERR_ILL;
	else if (signum == SIGTRAP)
		err = ERR_TRAP;
	else if (signum == SIGABRT)
		err = ERR_ABRT;
	else if (signum == SIGBUS)
		err = ERR_BUS;
	else if (signum == SIGFPE)
		err = ERR_FPE;
	else if (signum == SIGKILL)
		err = ERR_KILL;
	else if (signum == SIGTERM)
		err = ERR_TERM;
	else if (signum == SIGSTKFLT)
		err = ERR_STKFLT;
	else if (signum == SIGXCPU)
		err = ERR_XCPU;
	else if (signum == SIGXFSZ)
		err = ERR_XFSZ;
	return (err);
}

char		*ft_get_signalsusp(int signum, char *err)
{
	if (signum == SIGSTOP)
		err = ERR_STOP;
	else if (signum == SIGTSTP)
		err = ERR_TSTP;
	else if (signum == SIGTTIN)
		err = ERR_TTIN;
	else if (signum == SIGTTOU)
		err = ERR_TTOU;
	return (err);
}
