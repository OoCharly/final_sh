/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:57:17 by tboos             #+#    #+#             */
/*   Updated: 2017/01/08 15:57:21 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Searches the terminal name in config->env. If variable TERM exists,
**initializes the termcaps. usleep is depreciated in POSIX,
** we should use nanosleep
*/

void	ft_termcaps_init(t_config *config)
{
	char		*i;

	i = ft_strtabfindstart(config->env, "TERM=");
	if (i && tgetent(NULL, i + 5))
		config->term_state = 1;
	else
	{
		ft_error(SHNAME, ANSI_USE, BEAWARE_ERR, CR_ERROR);
		config->term_state = 0;
	}
}
