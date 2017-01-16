/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 12:26:47 by tboos             #+#    #+#             */
/*   Updated: 2017/01/09 05:12:45 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocomp.h"

/*
** print elem in appropriate padding.  If data_size = 1,
** Print element in video inverted
*/

void		ft_print_elem(t_list *list, t_stream *stream)
{
	if (!stream->config->syntax_color_off)
	{
		if (S_ISDIR(list->data_size))
			ft_putstr_fd(ANSI_COLOR_CYAN, SFD);
		else if (S_ISLNK(list->data_size))
			ft_putstr_fd(ANSI_COLOR_YELLOW, SFD);
		else if (S_ISREG(list->data_size)
				&& 00100 & list->data_size)
			ft_putstr_fd(ANSI_COLOR_GREEN, SFD);
		else if (S_ISCHR(list->data_size))
			ft_putstr_fd(ANSI_COLOR_BLUE, SFD);
		else if (S_ISBLK(list->data_size))
			ft_putstr_fd(ANSI_COLOR_RED, SFD);
		else if (S_ISFIFO(list->data_size))
			ft_putstr_fd(ANSI_COLOR_MAGENTA, SFD);
		else if (S_ISSOCK(list->data_size))
			ft_putstr_fd(ANSI_COLOR_MAGENTA, SFD);
	}
	if ((list->data_size & 1))
		ft_putstr_fd(ANSI_REVERSEVID, SFD);
	ft_putstrpad_fd(list->data, COMP_PAD, 'L', SFD);
	ft_putstr_fd(ANSI_COLOR_RESET, SFD);
}

/*
** Print a line each elem one after another
*/

void		ft_autocomp_print_line(t_list *list, size_t elem, t_stream *stream)
{
	size_t	new_elem;
	size_t	j;

	ft_print_elem(list, stream);
	if ((new_elem = elem + COMP_IN_COL) < COMP_SIZE_LIST)
	{
		stream->tput = "nd";
		ft_tputs(stream);
		ft_tputs(stream);
		j = COMP_IN_COL;
		while (j--)
			list = list->next;
		ft_autocomp_print_line(list, new_elem, stream);
	}
}

/*
** Print a line and make sure to return carriage before continuing.
*/

void		ft_autocomp_print_grid(size_t start, size_t end, t_stream *stream)
{
	size_t	j;
	t_list	*list;

	list = COMP_BEGIN_LIST;
	j = -1;
	while (++j < start)
		list = list->next;
	while (start < end && list)
	{
		ft_autocomp_print_line(list, start, stream);
		if (start != end - 1)
			ft_putchar_fd('\n', SFD);
		else
			ft_repeat_termcaps(COMP_COL, "le", stream);
		list = list->next;
		start++;
	}
}

/*
** Print only printable part and handle vertical scrolling.
*/

void		ft_autocomp_scroll(t_stream *stream)
{
	static int		start = 0;
	int				current;
	int				end;

	current = (int)COMP_CURRENT;
	while (current - (int)COMP_IN_COL > 0 || (current == (int)COMP_IN_COL))
		current -= COMP_IN_COL;
	end = start + COMP_DISPLAYABLE;
	if (current < start)
	{
		start = current;
		end = start + COMP_DISPLAYABLE;
	}
	else if (current >= end)
	{
		end = current + 1;
		start = end - COMP_DISPLAYABLE;
	}
	ft_autocomp_print_grid(start, end, stream);
	ft_repeat_termcaps((end - start + 1), "up", stream);
	ft_autocomp_underline(stream, 'U');
}

/*
** If oversize, return carriage for prompt.
** Else, come back to previous position.
*/

void		ft_comp_print(t_stream *stream)
{
	if (COMP_PAD >= COMP_COL)
		ft_underline_mess("Please resize term...", stream);
	else
	{
		get_col_elem(stream);
		ft_autocomp_underline(stream, 'D');
		if (ft_autocomp_is_oversize(stream))
			if (COMP_STATE == 1)
			{
				ft_autocomp_print_grid(0, COMP_IN_COL, stream);
				stream->tput = "do";
				ft_tputs(stream);
				ft_secure_prompt(stream);
				ft_flush_command(stream);
			}
			else
				ft_autocomp_scroll(stream);
		else
		{
			ft_autocomp_print_grid(0, COMP_IN_COL, stream);
			ft_repeat_termcaps(COMP_IN_COL, "up", stream);
			ft_autocomp_underline(stream, 'U');
		}
	}
}
