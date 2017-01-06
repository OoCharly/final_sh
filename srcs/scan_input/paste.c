#include "minishell.h"

static char	*ft_checkpaste(t_stream *stream)
{
	char	*match;
	char	*test;
	char	*mem;

	mem = NULL;
	match = stream->command;
	while ((test = match)
		&& (match = ft_strchr(match, '\n')))
	{
		*match = 0;
		if (!ft_matchchr(&test))
		{
			ft_push_history(stream, stream->config, 0);
			ft_incr_history(&(stream->config->hindex));
			mem = match + 1;
			ft_winsize();
			*match = ';';
			break;
		}
		else
			*match = '\n';
		++match;
	}
	return (mem);
}

int		ft_pastereturn(t_stream *stream)
{
	size_t	pos;
	char	*mem;

	if (ft_history_exclamation(stream))
		ft_winsize();
	pos = stream->pos;
	ft_gohome(stream);
	mem = ft_checkpaste(stream);
	if (mem)
	{
		stream->config->exclamation = ft_strdup(mem);
		*mem = 0;
		return (1);
	}
	ft_gomatch(stream, pos);
	return (0);
}
