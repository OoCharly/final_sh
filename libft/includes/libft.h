/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             */
/*   Updated: 2017/01/09 04:29:41 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "basics.h"
# include "list.h"
# include "dclist.h"
# include "get_next_line.h"
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

/*
** Standard Program Fonction
*/
void	ft_usage(char *name, char *usage);
void	ft_exit(int mode);
int		ft_status(int value);
/*
** CHAR <-> INT
*/
int		ft_atoi(char *str);
char	*ft_itoa(int n);
char	*ft_st_itoa(int n);
/*
** Padding et autre en attente printf
*/
void	ft_putcstr(char *str, char c, int size, char pos);
void	ft_putstrpad_fd(char *str, int size, char pos, int fd);
void	ft_putstrpad(char *str, int size, char pos);
void	ft_putcolendl(char *s, char *col);
void	ft_putstr_nbr_str(char *str, int nbr, char *mtab);
void	ft_putstr_str_str_fd(char *name, char *file, char *error, int fd);
void	ft_putstr_nbr_str(char *str, int nbr, char *mtab);
/*
** PRINT
*/
void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putendl(char *s);
void	ft_putnbr(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstrtab(char **s, char c);
void	ft_putstrtab_fd(char **s, char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstrlist(t_list *list, char c);
/*
** Tab Manipulation
*/
char	**ft_insertdeletetab(char **big, char **small, size_t index);
char	**ft_inserttab(char **big, char **small, size_t index);
char	*ft_getenv(char *name, char **env);
char	*ft_getenv_whole(char *name, char **env);
int		ft_igetenv(char *name, char **env);
/*
** DEBUG AND FEEDBACK 
*/
int		ft_ringbell_fd(int fd);

#endif
