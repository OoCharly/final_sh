/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:47:29 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 13:15:56 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMP_H
# define AUTOCOMP_H

# include "minishell.h"

# define COMP_PAD			stream->comp.pad
# define COMP_COL			stream->col
# define COMP_ROW			stream->row
# define COMP_SIZE_LIST		stream->comp.size_list
# define COMP_BEGIN_LIST	stream->comp.begin_list
# define COMP_IN_COL		stream->comp.in_col
# define COMP_STATE			stream->autocomp_state
# define COMP_CURRENT		stream->comp.current
# define COMP_BEGIN			stream->comp.begin
# define COMP_POS_COMMAND	stream->comp.command_pos
# define COMP_DISPLAYABLE	stream->comp.displayable
# define COMP_BUF			stream->comp.buf

/*
** auto_utils.c
*/

int		ft_is_separator(char c);
char	*get_begin(int i, char *str, size_t *len);

/*
** getenv.c
*/

int		ft_getenvline(char *str, char **e);
char	**ft_getenvtab(char *str, char **e);
void	get_size_list(t_stream *stream);
void	get_pad(t_stream *stream, char *str);
void	get_col_elem(t_stream *stream);

/*
** autocomp.c
*/

void	ft_autocomp(t_stream *stream);

/*
** buildlist.c
*/

void	build_list(char *str, int mode, t_stream *stream);

/*
** support.c
*/

int		ft_is_same_autocomp(t_stream *stream);
void	reset_autocomp(t_stream *stream);
void	ft_end_autocomp(t_stream *stream);
void	ft_repeat_termcaps(size_t time, char *term, t_stream *stream);
int		ft_autocomp_is_oversize(t_stream *stream);

/*
** print.c
*/

void	ft_print_elem(t_list *list, t_stream *stream);
void	ft_autocomp_print_line(t_list *list, size_t elem, t_stream *stream);
void	ft_autocomp_scroll(t_stream *stream);
void	ft_autocomp_print_grid(size_t start, size_t end, t_stream *stream);
void	ft_comp_print(t_stream *stream);

/*
** move.c
*/

void	ft_comp_get_down(t_stream *stream);
void	ft_comp_get_left(t_stream *stream);
void	ft_comp_get_up(t_stream *stream);
void	ft_comp_get_right(t_stream *stream);
void	ft_comp_select_current(size_t current, t_stream *stream, char mode);

/*
** command.c
*/

void	ft_autocomp_append(t_stream *stream);
void	ft_autocomp_delete(t_stream *stream);
void	ft_autocomp_underline(t_stream *stream, char mode);

/*
** rep.c
*/

int		ft_rep(t_stream *stream, char *begin);

#endif
