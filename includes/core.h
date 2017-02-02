/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:14:05 by tboos             #+#    #+#             */
/*   Updated: 2017/02/02 10:42:56 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# define SHNAME			"21sh"
# define HISTORY_SIZE	10
# define FT_PUTSTRFD	ft_putstr_str_str_fd
# define FREE			ft_freegiveone
# define BELL			ft_ringbell_fd
# define DPATH	"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

/*
** SHELL STATES
*/
# define RUNNING_COMMAND	1
# define SCANNING_COMMAND	2
# define SIGTSTP_COMMAND	3
# define SIGINT_COMMAND		4
# define RUNNING_SSHELL		5
# define RUNNING_SON		6

/*
** ft_signal modes
*/
# define SIGNAL_SET		0
# define SIGNAL_RESET	1
# define SIGNAL_SCRIPT	2
/*
** variables and functions 
*/
# define VAR_STD	001
# define VAR_TAB	002
# define VAR_FUN	004

/*
** Config Defines
*/
# define DOT		config->dot_sequence

typedef struct dirent	t_dirent;
typedef struct termios	t_termios;
typedef struct passwd	t_passwd;
typedef struct stat		t_st;
typedef struct	s_bin
{
	char		*name;
	char		*path_name;
}				t_bin;
typedef struct	s_var
{
	char		*name;
	void		*value;
	size_t		type;
}				t_var;
typedef struct	s_config
{
	int			shell_state;
	char		**env;
	t_list		*variables;
	char		*pwd;
	char		*pwd_subrep;
	size_t		prompt_len;
	t_list		*bin;
	t_list		*h_bin[34];
	t_termios	termios;
	t_termios	termios_backup;
	int			term_state;
	char		*history[HISTORY_SIZE + 1];
	char		*hist_newcmd[HISTORY_SIZE + 1];
	int			hindex;
	int			ncmd_index;
	char		*hloc;
	char		*hlocbis;
	char		*exclamation;
	int			heredoc;
	t_list		*jobs;
	char		*fg_sentence;
	char		*command;
	t_list		*chimera;
	t_list		*chimera_tail;
	pid_t		shell_pgid;
	char		dot_sequence;
	int			last_exit;
	bool		syntax_color_off;
	char		*last_hash;
	char		*visual_buf;
	char		script_state;
}				t_config;
/*
**error.c
*/
char			*ft_shname_or_file(char	*name);
size_t			ft_script_line(int mode);
int				ft_error(char *name, char *other, char *mess, int mode);
int				ft_initerror(t_config *config);
void			ft_lexer_error(char *command);
/*
**hash.c && cmp.c
*/
int				ft_pathtohash(t_config *config);
int				ft_return_binpath(t_config *config, char *name, char **path);
int				ft_scmp(void *data1, void *data2);
int				ft_proscmp(void *pid1, void *pid2);
int				ft_ascii_cmp(t_bin *s1, t_bin *s2);
/*
**free.c && free_pros.c && free_list.c
*/
void			ft_shell_exit(t_config *config);
void			ft_freebin(void *data, size_t data_size);
void			ft_free_config(t_config *config);
t_list			*ft_partial_freelist(t_list *begin, size_t n);
void			ft_list_free_av(void *data, size_t data_size);
void			ft_list_free_elem(t_list *elem);
t_list			*ft_freelist(t_list **begin);
void			ft_freepros(t_list *kill);
void			ft_free_one_process(t_list **process, pid_t pid);
void			ft_free_all_process(t_list **process, int mode);
void			ft_free_all_jobs(t_list **job);
/*
**main.c && minishell.c
*/
void			ft_run_command(t_config *config);
void			ft_minishell(t_config *config);
void			ft_print_list(t_list *elem);
/*
**signal.c
*/
int				ft_signal(int mode);
void			ft_signal_handle(int i);
void			ft_sigwinch(int mode);
/*
**signal_reset.c
*/
void			ft_signal_reset(void);
/*
** terminit.c
*/
void			ft_termcaps_init(t_config *config);
/*
** script.c
*/
void			ft_scripting(int fd, t_config *config, char *command);

/*
** debug.c
*/
void			ft_printchimera(t_list *chimera);

#endif
