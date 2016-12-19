/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_scan.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:14:44 by tboos             #+#    #+#             */
/*   Updated: 2016/12/19 14:58:09 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAN_INPUT_H
# define SCAN_INPUT_H

# define SFD stream->fd
# define TUP "\x1b[A"
# define TDO "\x1b[B"
# define TLE "\x1b[D"
# define TND "\x1b[C"
# define TDL "\x1b[K"
# define TCD "\x1b[J"
# define REPROMPT -10
# define STR_EOF -11

typedef struct	s_comp
{
	int			mode;
	size_t		command_pos;
	size_t		in_col;
	size_t		nb_col;
	size_t		pad;
	size_t		size_list;
	size_t		current;
	size_t		displayable;
	t_list		*begin_list;
	char		*begin;
	char		buf[256];
	char		**kill;
}				t_comp;

typedef struct	s_stream
{
	char		*tput;
	int			fd;
	int			ret;
	int			shindex;
	int			state;
	char		buf[256];
	char		*command;
	char		*kill;
	char		*search;
	size_t		pos;
	size_t		col;
	size_t		row;
	size_t		cur_col;
	size_t		autocomp_state;
	t_config	*config;
	t_comp		comp;

}				t_stream;

typedef struct	s_globing
{
	t_list		*lstmp;
	t_list		*lstprint;
	int			ret;
	int			mode;
	int			end;
	int			print;
	char		*path;
}				t_globing;
/*
**streamscan.c
*/
char			*ft_streamscan(t_config *config, t_stream *stream, int fd);
/*
**underlinemess.c
*/
void			ft_putmess(t_stream *stream, char *mess);
int				ft_underline_mess(char *mess, t_stream *stream);
/*
**quotecheck.c
*/
char			*ft_matchchr(char **str);
int				ft_quotecheck(t_stream *stream);
/*
**termcaps.c
*/
int				ft_putcharint(int	i);
void			ft_tputs(t_stream *stream);
void			ft_mvleft(t_stream *stream);
void			ft_mvright(t_stream *stream);
void			ft_gomatch(t_stream *stream, unsigned int go);
/*
**arrowlr.c && arrowud.c
*/
void			ft_ctrlleft(t_stream *stream);
void			ft_ctrlright(t_stream *stream);
void			ft_left(t_stream *stream);
void			ft_right(t_stream *stream);
void			ft_goend(t_stream *stream);
void			ft_gohome(t_stream *stream);
void			ft_ctrlup(t_stream *stream);
void			ft_ctrldown(t_stream *stream);
/*
**deletion.c
*/
void			ft_erase(t_stream *stream);
void			ft_clean_field(t_stream *stream);
void			ft_sup(t_stream *stream);
void			ft_del(t_stream *stream);
/*
**chrparse.c
*/
void			ft_append(t_stream *stream);
void			ft_flushend(t_stream *stream);
void			ft_flush(t_stream *stream);
int				ft_chrparse(t_stream *stream);
/*
**autocomp.c
*/
void			ft_autocomp(t_stream *stream);
/*
**globing.c
*/
void			ft_loop_path(t_stream *stream, t_globing *data);
int				ft_search_chr(char *str, char c);
int				ft_checkdir(t_stream *stream, t_list *list, t_globing *glob, char *path, char *needle);
/*
**outputfile.c
*/
void			ft_print_output(char *str);
/*
**prompt.c
*/
void			ft_prompt(t_config *config);
/*
**history.c
*/
void			ft_up(t_stream *stream);
void			ft_down(t_stream *stream);
void			ft_decr_history(int *hindex);
void			ft_incr_history(int *hindex);
void			ft_push_history(t_stream *stream, t_config *config, int mode);
void			ft_load_history(t_config *config);
void			ft_purge_history(t_config *config, char **hist, int index, int mode);
void			ft_searchengine(t_stream *stream);
void			ft_searchengineend(t_stream *stream);
void			ft_sappend(t_stream *stream);
void			ft_sdel(t_stream *stream);
void			ft_sprompt(t_stream *stream);
void			ft_searchinhistory(t_stream *stream);
void			ft_modifycommand(t_stream *stream);
void			ft_flushsearch(t_stream *stream);
/*
**winsize.c
*/
void			ft_winsize(void);
void			ft_prompt_reset(t_stream *stream);
void			ft_flush_command(t_stream *stream);
void			ft_secure_prompt(t_stream *stream);
/*
**checknewline.c
*/
int				ft_checknewline(t_stream *stream, size_t p);
/*
*syntax_color.c
*/
void			ft_syntax_color(t_stream *stream);
/*
** cursor.c
*/
size_t			ft_get_cur_col(char *cmd, size_t pos,  t_stream *stream);
/* 
**save.c
*/
t_stream		*ft_save_stream(t_stream *stream);
t_config		*ft_save_config(t_config *config);

#endif
