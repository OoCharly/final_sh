/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:10:40 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:17:37 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Put syntax_color_off at ON.
*/

void		ft_syntax_color(t_stream *stream)
{
	stream->config->syntax_color_off ^= 1;
}
