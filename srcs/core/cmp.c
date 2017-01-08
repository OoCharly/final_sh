/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 11:33:35 by tboos             #+#    #+#             */
/*   Updated: 2017/01/08 15:56:57 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_scmp(void *data1, void *data2)
{
	return (ft_strcmp((char *)data1, (char *)data2));
}

int			ft_proscmp(void *pid1, void *pid2)
{
	return (*((pid_t *)pid1) - *((pid_t *)pid2));
}

int			ft_ascii_cmp(t_bin *s1, t_bin *s2)
{
	return (s1->name[0] - s2->name[0]);
}
