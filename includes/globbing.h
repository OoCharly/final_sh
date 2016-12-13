/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:17:18 by cdesvern          #+#    #+#             */
/*   Updated: 2016/12/13 17:41:55 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H
# include "minishell.h"

# define SIZE 1000

typedef		struct	s_brace
{
	t_list	*all;
	t_list	*arg1;
	t_list	*arg2;
	char	sub[SIZE];
	int		size;
	char	jump;
}					t_brace;

/*
** globbing_support.c
*/

size_t	ft_size_list(t_list *begin);
int		ft_checkglob(char *arg);

/*
** globbing.c
*/
void	ft_glob(DIR *dir, char *path, char *glob);
char	*ft_launch_glob(char *str);

/*
** match.c
*/
int		ft_match(char *glob, char *comp);


/*
** braces.h
*/

char	*ft_launchbraces(char	*str);
t_list	*ft_braces(char	*str, char out);
int		ft_isbraces(char *str);

#endif
