/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:51:56 by tboos             #+#    #+#             */
/*   Updated: 2016/12/14 14:19:26 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Function called in parameter of ft_freelist. For any type in begin->data,
**calls the appropriate function of free.
*/

void			ft_list_free_av(void *data, size_t data_size)
{
	if (data_size == PIPE && data && ((t_pipe*)data)->others_fd)
		ft_strtabfree(((t_pipe*)data)->others_fd);
	if (!data_size && data)
		ft_strtabfree((char **)data);
	else if (data_size == OP || data_size == HEREDOC)
		ft_freegiveone(&data);
	else if (data_size == PIPE && data && ((t_pipe*)data)->others_fd &&
		((t_pipe*)data)->others_fd[0])
	{
		ft_strtabfree(((t_pipe*)data)->others_fd);
		ft_freegiveone(&data);
	}
	else if (data_size == SSHELL)
		ft_freelist((t_list **)&data);
}

t_list			*ft_freelist(t_list **begin)
{
	ft_lstdel(begin, ft_list_free_av);
	return (NULL);
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
