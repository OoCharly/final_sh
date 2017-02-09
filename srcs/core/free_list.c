/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:51:56 by tboos             #+#    #+#             */
/*   Updated: 2017/02/09 11:55:40 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_free_var(t_var *var)
{
	FREE((void**)&var->name);
	if (var->type == VAR_STD || var->type == VAR_FUN)
		FREE((void**)&var->value);
	else if (var->type == VAR_TAB)
	{
		ft_strtabfree((char**)var->value);
		var->value = NULL;
	}
}

/*
**Function called in parameter of ft_freelist. For any type in begin->data,
**calls the appropriate function of free.
*/

void			ft_list_free_av(void *data, size_t data_size)
{
	if (!data_size && data)
		ft_strtabfree((char **)data);
	else if (data_size == OP || data_size == HEREDOC)
		ft_freegiveone(&data);
	else if (data_size == PIPE && data)
	{
		if (((t_pipe*)data)->others_fd)
			ft_strtabfree(((t_pipe*)data)->others_fd);
		ft_freegiveone(&data);
	}
	else if (data_size == SSHELL)
		ft_freelist((t_list **)&data);
	else if (data_size == VAR && data)
	{
		ft_free_var(data);
		FREE(&data);
	}
}

t_list			*ft_freelist(t_list **begin)
{
	if (begin && *begin)
		ft_lstdel(begin, ft_list_free_av);
	return (NULL);
}

void			ft_list_free_elem(t_list *elem)
{
	ft_list_free_av(elem->data, elem->data_size);
	free(elem);
}

/*
**In begin, frees the n first elements and their contents.
*/

t_list			*ft_partial_freelist(t_list *begin, size_t n)
{
	t_list	*kill;

	if (n && begin)
	{
		kill = begin;
		while (n-- && begin)
		{
			begin = begin->next;
			kill->next = NULL;
			ft_freelist(&kill);
			kill = begin;
		}
	}
	return (begin);
}
