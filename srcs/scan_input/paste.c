#include "minishell.h"

static char	*ft_strchr_dodge(char *str, char c)
{
	while (str && *str)
	{
		if (*str == c)
			return (str);
		if (*str == '\'' || *str == '\"')
			if (ft_gonextquote(&str, *str))
				return (NULL);
		if (*str == '\\')
			++str;
		++str;
	}
	return (str);
}

static int	ft_checkpaste(t_stream *stream, char **err)
{
	char	*match;

	match = stream->command;
	while ((stream->command)
		&& (match = ft_strchr_dodge(match, '\n')))
	{
		*err = stream->command;
		if (*match || (match = NULL))
			*match = 0;
		if (!(*err = ft_matchchr(&(*err))))
		{
			stream->config->exclamation = match ? ft_strdup(match + 1)
				: stream->config->exclamation;
			return (1);
		}
		else if ((match = match ? match + 1 : NULL))
			*match = '\n';
	}
	return (0);
}

char		*ft_pastereturn(t_stream *stream)
{
	char	*err;
	size_t	pos;

	err = NULL;
	if (ft_history_exclamation(stream))
		ft_winsize();
	pos = stream->pos;
	ft_gohome(stream);
	if (ft_checkpaste(stream, &err))
	{
		ft_winsize();
		ft_goend(stream);
		return (NULL);
	}
	else
		ft_gomatch(stream, pos);
	return (err);
}
