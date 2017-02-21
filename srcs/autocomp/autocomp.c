/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:29 by tboos             #+#    #+#             */
/*   Updated: 2017/02/21 12:50:29 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Get new autocomp mode.
** 0 = Nothing's print, have to look in curent repository.
** 1 = Nothing's print, have to look in binary list.
** 2 = already print, haveve to go forward or update path.
** 3 = already print, still have to compare in binary.
*/

static int		get_mode(int len, char *str, t_stream *stream)
{
	int		i;
	char	co;

	co = 0;
	i = (stream->pos) - len - 1;
	if (str[i + 1] && (str[i + 1] == '.' || str[i + 1] == '/'))
		return (2);
	while (i > 0 && str[i] != '|' && str[i] != ';')
	{
		if (str[i] != ' ')
			co = 1;
		i--;
	}
	if (!len)
		return (!co ? 1 : 0);
	return (!co ? 3 : 2);
}

/*
** In state zero, list is created
*/

static void		ft_state_zero(t_stream *stream)
{
	size_t		len;
	char		*b;

	len = 0;
	if (stream->command && stream->command[0])
	{
		while (!ft_is_separator(stream->command[stream->pos])
				&& stream->command[stream->pos])
			ft_mvright(stream);
		b = get_begin(stream->pos - 1, stream->command, &len);
		COMP_BEGIN = ft_strsub(b, 0, len);
		if (ft_rep(stream, b))
			return ;
		COMP_MODE = get_mode(len, stream->command, stream);
		build_list(COMP_BEGIN, stream);
		FREE((void**)&COMP_KILL);
		if (COMP_PAD > COMP_ROW || !COMP_BEGIN_LIST)
		{
			ft_end_autocomp(stream);
			return ;
		}
		COMP_STATE = 1;
	}
}

/*
** In state 1 elem 0 is video inverted and command is completed with this elem.
*/

static void		ft_state_one(t_stream *stream)
{
	COMP_CURRENT = 0;
	ft_comp_select_current(COMP_CURRENT, stream, 'S');
	COMP_STATE = 2;
	COMP_POS_COMMAND = stream->pos;
	ft_autocomp_append(stream);
}

/*
** In state 2 the selected element is swap and the command updated.
*/

static void		ft_state_two(t_stream *stream)
{
	size_t current_tmp;

	current_tmp = COMP_CURRENT;
	if (((ssize_t *)(stream->buf))[0] == CHT)
		ft_comp_get_down(stream);
	else if (((ssize_t *)(stream->buf))[0] == LEF)
		ft_comp_get_left(stream);
	else if (((ssize_t *)(stream->buf))[0] == RIG)
		ft_comp_get_right(stream);
	else if (((ssize_t *)(stream->buf))[0] == UPP)
		ft_comp_get_up(stream);
	else if (((ssize_t *)(stream->buf))[0] == DOW)
		ft_comp_get_down(stream);
	else if (((ssize_t *)(stream->buf))[0] == SHCHT)
		ft_comp_get_up(stream);
	ft_autocomp_delete(stream);
	ft_comp_select_current(current_tmp, stream, 'U');
	ft_comp_select_current(COMP_CURRENT, stream, 'S');
	ft_autocomp_append(stream);
}

/*
** Main fonction for autocompletion.
** If COMP_SIZE_LIST = 1, the command line is updated.
** Else collumn are printed
*/

void			ft_autocomp(t_stream *stream)
{
	if (COMP_STATE == 1)
		ft_state_one(stream);
	else if (COMP_STATE == 2)
		ft_state_two(stream);
	else
		ft_state_zero(stream);
	if (COMP_SIZE_LIST == 1)
	{
		ft_comp_select_current(0, stream, 'S');
		ft_autocomp_append(stream);
		ft_end_autocomp(stream);
	}
	else if (COMP_BEGIN_LIST)
		ft_comp_print(stream);
}
