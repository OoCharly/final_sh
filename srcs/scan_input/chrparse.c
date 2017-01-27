/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:29:42 by tboos             #+#    #+#             */
/*   Updated: 2017/01/27 11:33:04 by cdesvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_pack_append(t_stream *stream, int match)
{
	ft_strchrsed(stream->buf, '\t', ' ');
	stream->search ? ft_sappend(stream) : ft_append(stream);
	if (ft_strchr(stream->buf, '\n') && !ft_pastereturn(stream))
		match = 0;
	return (match);
}

/*
 **               PARSE HEXA FOR KEY MAPPING
 ** printf("\nbuf   = %lx\n", ((ssize_t *)(stream->buf))[0]);
 ** printf("\nmatch = %lx\n", match[i]);
 */

static int		ft_chrmatch(t_stream *stream)
{
	static ssize_t		match[] = {CLF, 0, SUP, CHT, DEL, LEF, RIG, UPP, DOW,
		CLEF, CRIG, CUPP, CDOW, END, HOM, CRS, ESC, ALTS, CTRLL, 0, 0, 0, NUL};
	static ssize_t		visualmatch[] = {CLF, VISP, SUP, 0, DEL, LEF, RIG, 0, 0,
		CLEF, CRIG, CUPP, CDOW, END, HOM, 0, ESC, ALTS, CTRLL, VISD, VISY, NUL};
	int					i;

	i = 0;
	while (i < LEN_TABMATCH)
	{
		if (((ssize_t *)(stream->buf))[0] == (stream->visual ?
			visualmatch[i] : match[i]))
			return (i);
		i++;
	}
	if ((ft_isprint(stream->buf[0]) || ft_isspace(stream->buf[0]))
		&& !stream->visual)
		return (-1);
	return (-2);
}

/*
 ** Run the appropriate function for a key touched.
 */

int				ft_chrparse(t_stream *stream)
{
	int					match;
	static void			(*ftab[])(t_stream *) = {&ft_vispaste, &ft_sup,
		&ft_autocomp, &ft_del, &ft_left, &ft_right, &ft_up, &ft_down,
		&ft_ctrlleft, &ft_ctrlright, &ft_ctrlup, &ft_ctrldown, &ft_goend,
		&ft_gohome, &ft_searchengine, &ft_searchengineend, &ft_syntax_color,
		&ft_clear, &ft_viscut, &ft_viscopy};

	if (COMP_STATE == 2 && ((ssize_t*)(stream->buf))[0] == CLF)
		ft_end_autocomp(stream);
	else if (ft_is_same_autocomp(stream))
		(*ftab[2])(stream);
	else if (stream->buf[0])
	{
		if ((match = ft_chrmatch(stream)) == -1
				&& !ft_isonlychr(stream->buf, '\t'))
			match = ft_pack_append(stream, match);
		else if (match > 0)
			(*ftab[match - 1])(stream);
		if (!match || (match == 1 && stream->config->visual_buf
			&& ft_strchr(stream->config->visual_buf, '\n')
			&& !ft_pastereturn(stream)))
			return (0);
	}
	return (1);
}
