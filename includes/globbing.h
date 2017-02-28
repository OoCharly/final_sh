/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:12:41 by jmunoz            #+#    #+#             */
/*   Updated: 2017/02/27 19:07:15 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H
# include "minishell.h"

# define BRACES_SIZE 3000
# define GLOB_OCCUR_LIMIT 25000

typedef struct	s_brace
{
	t_list	*all;
	t_list	*arg1;
	t_list	*arg2;
	char	sub[BRACES_SIZE];
	int		size;
	char	jump;
}				t_brace;

/*
** globbing_support.c
*/
size_t			ft_size_list(t_list *begin);
int				ft_checkchars(char *arg, char *chars);
int				ft_closechar(char *arg, char *c);
DIR				*ft_opendir(const char *filename);
/*
** globbing.c
*/
void			ft_glob(DIR *dir, char *path, char *glob);
char			**ft_launch_glob(char *str);
/*
** match.c
*/
int				ft_match(char *glob, char *comp, char jump);
/*
** braces.c
*/
char			**ft_launchbraces(char *str);
t_list			*ft_braces(char	*str, char out);

#endif
