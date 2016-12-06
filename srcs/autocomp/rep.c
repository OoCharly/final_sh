#include "minishell.h"

static void	ft_rep_glob(t_stream *stream, char *b)
{
	char	*ret;
	size_t	size;
	size_t	pos;
	char	*tmp;

	if ((ret = ft_launch_glob(COMP_BEGIN)))
	{
		tmp = ret;
		pos = stream->pos;
		ft_gomatch(stream, b - stream->command);
		ft_memmove(b, stream->command + pos,
			strlen(stream->command + pos) + 1);
		ft_bzero(stream->buf, 256);
		while ((size = ft_strlen(ft_strncpy(stream->buf, ret, 255))) == 255)
		{
			ft_append(stream);
			ret = ret + size;
			ft_bzero(stream->buf, 256);
		}
		ft_append(stream);
	}
	ft_bzero(stream->buf, 256);
	ft_freegiveone((void**)&tmp);
}

int		ft_rep(t_stream *stream, char *b)
{
	if (COMP_BEGIN && !(ft_strchr(COMP_BEGIN, '"')) && (ft_strchr(COMP_BEGIN, '*')
				|| ft_strchr(COMP_BEGIN, ']') || ft_strchr(COMP_BEGIN, '[') ||
				ft_strchr(COMP_BEGIN, '?')))
	{
		ft_rep_glob(stream, b);
		return (1);
	}
	return (0);
}
