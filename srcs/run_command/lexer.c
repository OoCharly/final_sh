/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:05:45 by tboos             #+#    #+#             */
/*   Updated: 2017/02/27 18:47:19 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Returns the index i of cmd, where the pattern matchs with on of these
**operators ><|&;()#. If an escapement pattern before quote is meeted, the
**function doesn't takes care about what there are between quotes.
*/

int				ft_next_op(char *cmd, size_t i)
{
	while (cmd[i] && !ft_strchr("><|&;()#", cmd[i]))
		i = ft_increm_dodge_quotes(cmd, i);
	if (cmd[i] == '(' && ft_test_emptyness(cmd, i + 1, ')')
		&& ft_test_emptyness(cmd, 0, '(')
		&& ft_error(SHNAME, NULL, ANONIMOUS_ERR, 1 | EEXIT))
		return (0);
	if (cmd[i] == '(' && i && cmd[i - 1] == '=' && (i = ft_gonext_par(cmd, i)))
		return (ft_next_op(cmd, i));
	if (cmd[i] == '(' && i && !ft_test_emptyness(cmd, 0, '(')
		&& ft_test_emptyness(cmd, i + 1, ')') && (i = ft_gonext_par(cmd, i)))
	{
		if (!ft_isspace(cmd[i]) && ft_error(SHNAME, NULL,
			SPA_BEF_B_ERR, 1 | EEXIT))
			return (0);
		while (ft_isspace(cmd[i]))
			++i;
		if (cmd[i] != '{' && ft_error(SHNAME, NULL, F_NEED_BRA_ERR, 1 | EEXIT))
			return (0);
		ft_gonext_par(cmd, i);
		++i;
		return (ft_next_op(cmd, i));
	}
	if (cmd[i] == '#' && (!i || ft_isspace(cmd[i - 1])))
		cmd[i] = 0;
	return (i);
}

static t_list	*ft_op_handle(char *cmd, size_t *i)
{
	t_list	*next;
	t_list	*op;

	if (!(next = ft_av_handle(cmd, *i)))
		return (NULL);
	else if (cmd[*i] == '(' && ft_test_emptyness(cmd, *i + 1, ')')
			&& ft_error(SHNAME, "parse error", "empty sshell", CR_ERROR)
			&& !ft_freelist(&next))
		return (NULL);
	else if (cmd[*i] == '(' && ++(*i))
		return (ft_lexer_sshell_on(cmd, i, next));
	else if (cmd[*i] == ')')
		return (next);
	else if (cmd[*i])
	{
		if (!(next->next = (t_list *)ft_memalloc(sizeof(t_list)))
				&& ft_error(SHNAME, "lexer", "malloc error", CR_ERROR))
			return (ft_freelist(&next));
		op = next->next;
		op->data_size = 1;
		if (!(op->data = (void*)ft_match_op(cmd, i, next)))
			return (ft_freelist(&next));
		if (!ft_strcmp(op->data, "<<"))
			op->data_size = HEREDOC;
	}
	return (next);
}

t_list			*ft_built_couple(char *cmd, size_t *i)
{
	t_list	*next;

	if (!(*i = ft_next_op(cmd, *i)) && (!cmd[*i] ||
			(cmd[*i] == '(' && ft_test_emptyness(cmd, *i + 1, ')'))))
		return (NULL);
	if (*i && (cmd[*i] == '>' || cmd[*i] == '<'))
		while (*i && ft_isdigit(cmd[*i - 1]))
			(*i)--;
	if (!(next = ft_op_handle(cmd, i)))
		return (ft_freelist(&next));
	return (next);
}

t_list			*ft_lexer(char *cmd)
{
	size_t	i;
	t_list	*begin;
	t_list	*next;

	begin = NULL;
	i = 0;
	while (ft_isspace(*cmd))
		++cmd;
	while ((cmd = cmd + i)
		&& !(i = 0) && *cmd && *cmd != ')')
	{
		while (ft_isspace(*cmd))
			++cmd;
		if (!*cmd)
			break ;
		if (!(next = ft_built_couple(cmd, &i)))
			return (ft_freelist(&begin));
		ft_list_push_back(&begin, next);
	}
	ft_lexer_sshell_off(cmd, i);
	return (begin);
}
