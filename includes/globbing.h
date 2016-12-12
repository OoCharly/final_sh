/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:17:18 by cdesvern          #+#    #+#             */
/*   Updated: 2016/12/12 16:00:46 by maxpetit         ###   ########.fr       */
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

/*
** match.c
*/
int		ft_match(char *glob, char *comp);

#endif
