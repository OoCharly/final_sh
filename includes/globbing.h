/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:17:18 by cdesvern          #+#    #+#             */
/*   Updated: 2016/12/06 13:20:49 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H

# include "minishell.h"

/*
** globbing.c
*/

void	ft_glob(DIR *dir, char *path, char *glob);
char	*ft_launch_glob(char *str);
int		ft_insertglob(t_list *begin);

/*
** match.c
*/

int		ft_match(char *glob, char *comp);

#endif
