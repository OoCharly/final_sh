/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectpipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 12:13:28 by rbaran            #+#    #+#             */
/*   Updated: 2017/02/01 17:27:42 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_newpipe(int mode)
{
	int		*pip;
	t_list	*new;

	if (!(pip = (int *)ft_memalloc(sizeof(t_pipe)))
			&& ft_error(SHNAME, "parser", "malloc error on pipe", CR_ERROR))
		return (NULL);
	if (mode != 2 && -1 == pipe(pip)
			&& ft_error(SHNAME, "parser", "pipe error", CR_ERROR)
			&& ft_freegiveone((void**)pip))
		return (NULL);
	if (mode)
	{
		if (!(new = (t_list*)ft_memalloc(sizeof(t_list)))
				&& ft_error(SHNAME, "parser", "malloc error on pipe", CR_ERROR))
			return (NULL);
		new->data_size = PIPE;
		new->data = pip;
		return ((void*)new);
	}
	return ((void*)pip);
}

static int	ft_redirectheredoc(t_list *begin, t_list **rhead, t_config *config,
		int **r_pipe)
{
	int		i;

	close((*r_pipe)[0]);
	close((*r_pipe)[1]);
	if (pipe(*r_pipe) == -1)
		return (1 ^ ft_error(SHNAME, "parser", "pipe heredoc error", CR_ERROR));
	i = 0;
	while (((char**)((*rhead)->next->data))[++i])
	{
		write((*r_pipe)[1], ((char**)((*rhead)->next->data))[i],
				ft_strlen(((char**)((*rhead)->next->data))[i]));
		write((*r_pipe)[1], "\n", 1);
	}
	*rhead = ft_partial_freelist(*rhead, 2);
	return (ft_node_descriptors(begin, rhead, config, r_pipe));
}

int			ft_redirectpipe(char *file, int *pip, char *tmp)
{
	int		flags;
	int		fd;

	flags = 0;
	fd = -1;
	if ((!file || !tmp)
			&& ft_error(SHNAME, "parser", "redirection error", CR_ERROR))
		return (0);
	if (!ft_strcmp(tmp, ">"))
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (!ft_strcmp(tmp, ">>"))
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else if (!ft_strcmp(tmp, "<"))
		flags = O_RDONLY;
	if (!ft_access_file(file, flags)
		|| ((fd = open(file, flags, RDEFAULT)) == -1
		&& (fd = open(file, flags)) == -1
		&& ft_error(SHNAME, file, "open error", CR_ERROR)))
		return (0);
	if (!pip)
		return (fd);
	(flags == O_RDONLY) ? dup2(fd, pip[0]) : dup2(fd, pip[1]);
	close(fd);
	return (1);
}

static int	ft_agregate(t_list *begin, t_list **rhead, t_config *config,
		int **r_pipe)
{
	char	*tmp;

	tmp = (char*)(*rhead)->data;
	if (ft_isdigit(tmp[0]) || ft_strlen(tmp) > 2)
	{
		BOTHER_FD = ft_strtabadd_free(BOTHER_FD, tmp);
		(*rhead)->data = NULL;
		if (!ft_strchr(tmp, '&'))
		{
			BOTHER_FD = ft_strtabadd(BOTHER_FD,
				((char**)(*rhead)->next->data)[0]);
			ft_freegiveone((void**)&(*rhead)->next->data);
		}
		*rhead = ft_partial_freelist(*rhead, 2);
		return (ft_node_descriptors(begin, rhead, config, r_pipe));
	}
	else if (tmp[0] == '>' && !ft_redirectpipe((*rhead)->next ?
			((char**)(*rhead)->next->data)[0] : NULL, begin->next->data, tmp))
		return (0);
	else if (tmp[0] == '<' && !ft_redirectpipe((*rhead)->next ?
			((char**)(*rhead)->next->data)[0] : NULL, *r_pipe, tmp))
		return (0);
	*rhead = ft_partial_freelist(*rhead, 2);
	return (ft_node_descriptors(begin, rhead, config, r_pipe));
}

int			ft_node_descriptors(t_list *begin, t_list **rhead, t_config *config,
		int **r_pipe)
{
	char	*tmp;

	if (begin->next == *rhead)
		begin->next = NULL;
	if (*rhead && (tmp = ((char*)(*rhead)->data)))
	{
		if ((tmp[0] == '|' || tmp[0] == '>') && ((begin->next
			&& !((int*)begin->next->data)[0]
			&& -1 == pipe((int*)begin->next->data)) || (!begin->next
			&& !(begin->next = ft_newpipe(1)))))
			return (0);
		if ((ft_isdigit(tmp[0]) || ft_strlen(tmp) > 2)
				&& !begin->next && !(begin->next = ft_newpipe(2)))
			return (0);
		if (tmp[0] == '<' && !*r_pipe && !(*r_pipe = ft_newpipe(0)))
			return (0);
		if (!ft_strcmp(tmp, "<<"))
			return (ft_redirectheredoc(begin, rhead, config, r_pipe));
		if (tmp[0] == '<' || tmp[0] == '>'
					|| ft_isdigit(tmp[0]) || ft_strlen(tmp) > 2)
			return (ft_agregate(begin, rhead, config, r_pipe));
		if (tmp[0] == '|')
			*rhead = ft_partial_freelist(*rhead, 1);
	}
	return (1);
}
