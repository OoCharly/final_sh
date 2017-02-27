/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:56:22 by maxpetit          #+#    #+#             */
/*   Updated: 2017/02/27 18:19:31 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

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
# define ECHO_MINE	0x02
# define ECHO_MAJE	0x04

/*
**jobs builtin defines
*/
# define JOBS_FG	0
# define JOBS_BG	1
# define P_PARAM	1
# define L_PARAM	2

/*
**builtin.c && environ.c
*/
int				ft_is_no_fork_builtin(char **argv, t_config *config);
int				ft_default_env(t_config *config);
int				ft_builtin(char **argv, t_config *config);
void			ft_update_prompt(t_config *config);
void			ft_cd(char **argv, t_config *config);
char			*ft_resolve_symlink(char *path);
void			ft_env(char **argv, t_config *config);
void			ft_setenv(char *name, char *value, t_config *config);
void			ft_readysetenv(char **argv, t_config *config);
void			ft_unsetenv(char **argv, t_config *config);
void			ft_echo(char **argv);
int				ft_cslink(char *path);
/*
**jobs.c && jobs_utils.c
*/
int				ft_cmp_jobs(t_list *s, char *description, int i);
void			ft_print_jobs(t_list *sentence, char *description);
void			ft_jobs(char **argv, t_config *config);
void			ft_fgbg(char **argv, t_config *config, int mode);
t_list			*ft_extract_job(t_config *config, char *description);
/*
**history.c
*/
int				ft_is_memerizable(char *cmd);
void			ft_history(char **argv, t_config *config);
char			*ft_return_hloc(char *hloc, int mode);
int				ft_count_line_file(t_config *config);
/*
**history_params.c
*/
void			ft_manage_param(char **argv, int i, t_config *config);
/*
**exclamation.c
*/
int				ft_history_exclamation(t_stream *stream);
int				ft_history_rep(t_stream *stream);
/*
**unset_export.c
*/
void			ft_export(char **argv, t_config *config);
void			ft_unset(char **argv, t_config *config);
#endif
