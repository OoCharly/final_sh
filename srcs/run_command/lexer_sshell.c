/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_sshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:10:12 by tboos             #+#    #+#             */
/*   Updated: 2016/11/14 09:16:39 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_save_cmd(char *cmd)
{
	static char *save = NULL;

	if (cmd)
		save = cmd;
	return (save);
}

static t_list	*ft_fill_data_update_index(char *cmd, size_t *i, t_list *next)
{
	if (next->data && ((char**)next->data)[0]
			&& ft_error(SHNAME, PARSE_ERR, ((char**)next->data)[0], 1))
		return (ft_freelist(&next));
	ft_list_free_av(next->data, next->data_size);
	next->data_size = SSHELL;
	if (!(next->data = ft_lexer(cmd + *i)))
		return (ft_freelist(&next));
	*i = ft_save_cmd(NULL) - cmd;
	return (next);
}

t_list			*ft_lexer_sshell_on(char *cmd, size_t *i, t_list *next)
{
	size_t		j;
	t_list		*test;

	if (!(next = ft_fill_data_update_index(cmd, i, next)))
		return (NULL);
	cmd += *i;
	while (ft_isspace(*cmd) && ++(*i))
		++cmd;
	j = 0;
	if (*cmd && *cmd != ')' && (test = ft_built_couple(cmd, &j)))
	{
		if (test->data && ((char**)test->data)[0]
			&& ft_error(SHNAME, PARSE_ERR, ((char**)test->data)[0], 1)
			&& !ft_freelist(&test))
			return (ft_freelist(&next));
		ft_list_push_back(&next, test->next);
		test->next = NULL;
		ft_freelist(&test);
	}
	*i += j;
	return (next);
}

void			ft_lexer_sshell_off(char *cmd, size_t i)
{
	(void)i;
	ft_save_cmd(cmd + 1);
}
