/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:14:05 by tboos             #+#    #+#             */
/*   Updated: 2016/12/08 10:31:24 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# define SHNAME			"21sh"
# define HISTORY_SIZE	100
# define FT_PUTSTRFD	ft_putstr_str_str_fd
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
**Env builtin defines (params)
*/
# define ENV_I		0x01
# define ENV_H		0x02
# define ENV_HELP	"--help"
# define ENV_UNSET	"--unset"
# define ENV_IGNORE	"--ignore-environment"

/*
**Echo builtin defines (params)
*/
# define ECHO_N		0x01

/*
**jobs builtin defines
*/
# define JOBS_FG	0
# define JOBS_BG	1

/*
** ft_signal modes
*/
# define SIGNAL_SET		0
# define SIGNAL_RESET	1
# define SIGNAL_SCRIPT	2

typedef struct dirent	t_dirent;
typedef struct termios	t_termios;
typedef struct passwd	t_passwd;
typedef struct stat		t_st;
typedef struct	s_bin
{
	char		*name;
	char		*path_name;
}				t_bin;

typedef struct	s_config
{
	int			shell_state;
	char		**env;
	char		*pwd;
	char		*pwd_subrep;
	size_t		prompt_len;
	t_list		*bin;
	t_list		*h_bin[34];
	t_termios	termios;
	t_termios	termios_backup;
	int			term_state;
	char		*history[HISTORY_SIZE + 1];
	int			hindex;
	char		*hloc;
	int			heredoc;
	t_list		*jobs;
	char		*fg_sentence;
	char		*command;
	t_list		*chimera;
	t_list		*chimera_tail;
	char		dot_sequence;
	int			last_exit;
	bool		syntax_color_off;
	char		*last_hash;
}				t_config;
/*
**builtin.c && environ.c
*/
int				ft_is_no_fork_builtin(char **argv, t_config *config);
int				ft_default_env(t_config *config);
int				ft_builtin(char **argv, t_config *config);
void			ft_update_pwd(t_config *config);
void			ft_cd(char **argv, t_config *config);
void			ft_env(char **argv, t_config *config);
void			ft_setenv(char *name, char *value, t_config *config);
void			ft_readysetenv(char **argv, t_config *config);
void			ft_unsetenv(char **argv, t_config *config);
void			ft_echo(char **argv);
/*
**jobs.c && jobs_utils.c
*/
int				ft_cmp_jobs(t_list *s, char *description, int i);
void			ft_print_jobs(t_list *sentence, char *description);
void			ft_jobs(char **argv, t_config *config);
void			ft_fgbg(char **argv, t_config *config, int mode);
/*
**error.c
*/
char			*ft_shname_or_file(char	*name);
size_t			ft_script_line(int mode);
int				ft_error(char *name, char *other, char *mess, int mode);
int				ft_initerror(t_config *config);
void			ft_lexer_error(char *command);
char			*ft_qerr(char *err);
/*
**hash.c && cmp.c
*/
int				ft_pathtohash(t_config *config);
int				ft_return_binpath(t_config *config, char *name, char **path);
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
**history.c
*/
void			ft_history(char **argv, t_config *config);

#endif
