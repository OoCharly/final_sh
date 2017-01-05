/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesvern <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:17:18 by cdesvern          #+#    #+#             */
/*   Updated: 2017/01/04 21:35:50 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H
# include "minishell.h"

# define BRACES_SIZE 3000

typedef		struct	s_brace
{
	t_list	*all;
	t_list	*arg1;
	t_list	*arg2;
	char	sub[BRACES_SIZE];
	int		size;
	char	jump;
}					t_brace;

/*
** globbing_support.c
*/

size_t	ft_size_list(t_list *begin);
int		ft_checkchars(char *arg, char *chars);

/*
** globbing.c
*/

void	ft_glob(DIR *dir, char *path, char *glob);
char	*ft_launch_glob(char *str);

/*
** match.c
*/

int		ft_match(char *glob, char *comp, char jump);


/*
** braces.c
*/

char	*ft_launchbraces(char	*str);
void	ft_braces2(t_brace *b, char *str);
t_list	*ft_braces(char	*str, char out);

#endif
