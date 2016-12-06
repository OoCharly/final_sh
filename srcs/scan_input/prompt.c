/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 16:37:59 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 10:15:19 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_prompt(t_config *config)
{
	t_stream	*stream;

	stream = ft_save_stream(NULL);
	if (!config->heredoc)
	{
		if (!config->last_exit)
			ft_putstr_fd("\x1b[34m-> \x1b[1;32m", SFD);
		else
			ft_putstr_fd("\x1b[31m-> \x1b[1;32m", SFD);
	}
	ft_putstr_fd(config->pwd_subrep, SFD);
	if (!config->heredoc)
		ft_putstr_fd(" : \x1b[0m", SFD);
}
