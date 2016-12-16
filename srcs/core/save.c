/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 14:19:22 by maxpetit          #+#    #+#             */
/*   Updated: 2016/12/16 14:25:54 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stream		*ft_save_stream(t_stream *stream)
{
	static t_stream	*saved = NULL;

	if (stream)
		saved = stream;
	return (saved);
}

t_config		*ft_save_config(t_config *config)
{
	static t_config *saved = NULL;

	if (config)
		saved = config;
	return (saved);
}
