/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_multiple_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 12:29:45 by tboos             #+#    #+#             */
/*   Updated: 2016/11/14 12:29:48 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_dup_fds(char *op, char *ampersand, char *file, int *fd)
{
	int	tmpfd;

	if (ampersand && op[0] == '>' && -1 == dup2(fd[1], fd[0]))
		ft_error(SHNAME, "bad file descriptor", ft_st_itoa(fd[0]), CR_ERROR);
	else if (ampersand && op[0] == '<' && -1 == dup2(fd[0], fd[1]))
		ft_error(SHNAME, "bad file descriptor", ft_st_itoa(fd[1]), CR_ERROR);
	else if (!ampersand)
	{
		if (!(tmpfd = ft_redirectpipe(file, NULL, op)))
			return ;
		if (op[0] == '>' && -1 == dup2(tmpfd, fd[0]))
			ft_error(SHNAME, "bad file descriptor", ft_st_itoa(fd[0]), 1);
		else if (op[0] == '<' && -1 == dup2(fd[0], tmpfd))
			ft_error(SHNAME, "bad file descriptor", ft_st_itoa(fd[0]), 1);
		close(tmpfd);
	}
}

void		ft_handle_multiplefd(char **others_fd)
{
	int		i;
	char	*op;
	char	*ampersand;
	int		fd[2];

	i = -1;
	while (others_fd[++i] && !(fd[0] = 0)
		&& !(fd[1] = 0))
	{
		op = others_fd[i] + ft_next_op(others_fd[i], 0);
		fd[0] = ft_atoi(others_fd[i]);
		if (!fd[0] && others_fd[i][0] != '0')
			fd[0] = 1;
		if ((ampersand = ft_strchr(op, '&')))
		{
			*ampersand = 0;
			fd[1] = ft_atoi(ampersand + 1);
			if (*(ampersand + 1) == '-')
				ft_dup_fds(op, NULL, "/dev/null", fd);
			else
				ft_dup_fds(op, ampersand, NULL, fd);
		}
		else
			ft_dup_fds(op, NULL, others_fd[++i], fd);
	}
}
