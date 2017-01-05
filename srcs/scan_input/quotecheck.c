/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotecheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:28:55 by tboos             #+#    #+#             */
/*   Updated: 2017/01/05 17:47:28 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_backslash(char **str)
{
	if (**str == '\\')
		++(*str);
	if (**str)
		++(*str);
	else
		return (BACK_ERR);
	return (NULL);
}

static char	*ft_gonext(char **str, char c)
{
	char		*test;

	++(*str);
	if ((test = ft_matchchr(str)))
	{
		if (test[1] == c)
			return (NULL);
		else
			return (test);
	}
	else if (c == ')')
		return (PAR_ERR);
	else
		return (BAQU_ERR);
}

static char	*ft_gonextquote(char **str, char c)
{
	++(*str);
	while (**str && **str != c)
		if (ft_backslash(str))
			return (BACK_ERR);
	if (**str != c)
	{
		if (c == '\'')
			return (SQUOTE_ERR);
		if (c == '\"')
			return (DQUOTE_ERR);
	}
	return (NULL);
}

char		*ft_matchchr(char **str)
{
	char		*test;

	while (**str && !(test = NULL))
	{
		if (**str == ')')
			return (UPAR_ERR);
		if (**str == '(' && (test = ft_gonext(str, ')')))
			return (test);
		if (**str == '`' && (test = ft_gonext(str, '`')))
			return (test);
		if (**str == '#')
			break ;
		if (**str == '\'' && (test = ft_gonextquote(str, **str)))
			return (test);
		if (**str == '\"' && (test = ft_gonextquote(str, **str)))
			return (test);
		if (ft_backslash(str))
			return (BACK_ERR);
	}
	**str = 0;
	return (NULL);
}

int			ft_quotecheck(t_stream *stream)
{
	char		*test;

	test = stream->command;
	ft_goend(stream);
	if (test && ft_history_exclamation(stream))
	{
		stream->state = REPROMPT;
		stream->config->exclamation = ft_strdup(stream->command);
	}
	else if ((test = ft_matchchr(&test)))
	{
		ft_append(stream);
		ft_repeat_termcaps(1, "cd", stream);
		return (ft_underline_mess(test + 2, stream));
	}
	return (1);
}
