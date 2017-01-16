/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotecheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 14:28:55 by tboos             #+#    #+#             */
/*   Updated: 2017/01/05 18:45:16 by maxpetit         ###   ########.fr       */
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

static char	*ft_gonext(char **str)
{
	char		c;
	char		*test;

	c = **str;
	++(*str);
	if ((test = ft_matchchr(str)))
	{
		if ('(' == c && **str == ')')
			return (NULL);
		if ('{' == c && **str == '}')
			return (NULL);
		if ('`' == c && test[1] == '`')
			return (NULL);
		return (test);
	}
	else if (c == '(')
		return (PAR_ERR);
	else if (c == '{')
		return (BRA_ERR);
	return (BAQU_ERR);
}

char		*ft_gonextquote(char **str, char c)
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

	test = NULL;
	while (**str)
	{
		if (**str == ')')
			return (UPAR_ERR);
		if (**str == '}')
			return (UBRA_ERR);
		if (**str == '(' && (test = ft_gonext(str)))
			return (test);
		if (**str == '{' && (test = ft_gonext(str)))
			return (test);
		if (**str == '`' && (test = ft_gonext(str)))
			return (test);
		if (**str == '#')
			break ;
		if (**str == '\'' && (test = ft_gonextquote(str, **str)))
			return (test);
		if (**str == '\"' && (test = ft_gonextquote(str, **str)))
			return (test);
		if (ft_backslash(str) && *(*str - 1) == '\\')
			return (BACK_ERR);
	}
	return (NULL);
}

int			ft_quotecheck(t_stream *stream)
{
	char		*test;

	test = stream->command;
	ft_goend(stream);
	ft_repeat_termcaps(1, "cd", stream);
	if (test && ft_history_exclamation(stream))
	{
		stream->state = REPROMPT;
		stream->config->exclamation = ft_strdup(stream->command);
	}
	else if (test && (test = ft_pastereturn(stream)))
	{
		ft_strcpy(stream->buf, "\n\0");
		ft_append(stream);
		return (ft_underline_mess(test + 2, stream));
	}
	return (1);
}
