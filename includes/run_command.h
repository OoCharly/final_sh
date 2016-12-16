/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:12:46 by tboos             #+#    #+#             */
/*   Updated: 2016/12/16 16:16:10 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_COMMAND_H
# define RUN_COMMAND_H

# include "minishell.h"

/*
** POLYMORPHIC CHAINLIST
*/
# define OP			1
# define PIPE		13
# define HEREDOC	3
# define SSHELL		4
# define PROS		100
# define SENT		101
# define JOB		102

/*
** MOST USED DEFFERENTIATION
*/
# define BDATA		((char*)begin->data)
# define SNDATA		((char*)src->next->data)
# define BNDATA		((char**)begin->next->data)[0]
# define BOTHER_FD	((t_pipe*)begin->next->data)->others_fd
# define RDEFAULT	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

typedef struct	s_pipe
{
	int			fixed_pip[2];
	char		**others_fd;
}				t_pipe;

/*
**exec.c
*/
char			*ft_path_handle(char **argv, t_config *config);
void			ft_execve(char *path, char **argv, char **env);
void			ft_launch_process(char *path, char **argv, t_config *config);
void			ft_kill_father(t_config *config);
/*
**files.c
*/
int				ft_access_file(char *path, int flags);
int				ft_access_dir(char const *path);
int				ft_access_exec(char *path, char **argv, t_config *config);
/*
**lexer.c
*/
t_list			*ft_lexer(char *cmd);
char			*ft_envvarinsert(char *cmd, size_t *i, t_config *config);
t_list			*ft_built_couple(char *cmd, size_t *i);
t_list			*ft_av_handle(char *cmd, size_t i);
int				ft_dodge_quote(char *cmd, size_t i);
char			*ft_match_op(char *cmd, size_t *i);
int				ft_next_op(char *cmd, size_t i);
void			ft_lexer_sshell_off(char *cmd, size_t i);
t_list			*ft_lexer_sshell_on(char *cmd, size_t *i, t_list *next);
/*
**parser.c
*/
char			*ft_save_cmd(char *cmd);
int				ft_node_descriptors(t_list *begin, t_list **rhead,
				t_config *config, int **r_pipe);
int				ft_build_pipe(t_list *begin, t_config *config, int **r_pipe);
void			ft_parse(t_config *config);
t_list			*ft_run_sentence(t_list *begin, t_config *config, int *r_pipe);
int				ft_redirectpipe(char *file, int *pip, char *tmp);
/*
**parser_multiple_fd.c
*/
void			ft_handle_multiplefd(char **others_fd);
/*
**wait.c
*/
void			ft_wait_sentence(t_list *job, t_config *config);
int				ft_build_sentence(t_list *begin, t_config *config);
/*
**heredoc.c
*/
int				ft_quote(t_list *begin, t_config *config);
int				ft_herringbone(t_list *begin, t_config *config);
/*
**insert.c
*/
int				ft_insert_loop(t_list *begin);
int				ft_check_insert(char ***t, int mode);
/*
**history_replace.c
*/
char			*ft_create_strhistidx(char *str);
int				ft_checkhist(char *str);

#endif
