/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <rbaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:33:52 by rbaran            #+#    #+#             */
/*   Updated: 2016/11/18 14:13:30 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_backsed(char *str)
{
	while (str && *str)
	{
		if (*str == '\\')
		{
			if (*(str + 1) == 'a')
				*str = '\a';
			else if (*(str + 1) == 'b' || *(str + 1) == 't')
				*str = *(str + 1) == 't' ? '\t' : '\b';
			else if (*(str + 1) == 'v' || *(str + 1) == 'n')
				*str = *(str + 1) == 'v' ? '\v' : '\n';
			else if (*(str + 1) == 'f' || *(str + 1) == 'r')
				*str = *(str + 1) == 'f' ? '\f' : '\r';
			else if (*(str + 1) == '0' || *(str + 1) == '\\')
				*str = *(str + 1) == '0' ? '\0' : '\\';
			else if (!*(str + 1))
				break ;
			else if (str += 2)
				continue ;
			ft_strcpy(str + 1, str + 2);
		}
		++str;
	}
}

static int	ft_parseparams(char **argv, int *param)
{
	int	i;

	i = 0;
	while (argv[++i] && argv[i][0] == '-')
	{
		if (argv[i][1] == 'n')
			*param |= ECHO_N;
		else if (argv[i][1] == 'e')
			*param |= ECHO_MINE;
		else if (argv[i][1] == 'E')
			*param |= ECHO_MAJE;
	}
	return (i);
}

void		ft_echo(char **argv)
{
	int	i;
	int	param;

	param = 0;
	i = ft_parseparams(argv, &param);
	while (argv[i])
	{
		ft_backsed(argv[i]);
		ft_putstr(argv[i]);
		if (argv[++i])
			ft_putchar(' ');
	}
	if (!(param & ECHO_N))
		ft_putchar('\n');
}
