/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_av.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:03:47 by tboos             #+#    #+#             */
/*   Updated: 2016/11/17 18:09:18 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**Fills t with any words meets in m.
*/

static char	**sft_tabdup(char **t, char *m, int nb)
{
	int		i;

	i = 0;
	while (nb--)
	{
		if (!(t[i++] = ft_strdup(m)))
		{
			ft_strtabfree(t);
			return (NULL);
		}
		else if (nb)
		{
			m += ft_strlen(m) + 1;
			while (ft_isspace(*m))
				m++;
		}
	}
	return (t);
}

/*
**Browses s string and puts an \0 at the end of any words. Counts number of
**words and return malloced table of av.
*/

char		**ft_strdodgesplit(char *s)
{
	char	**t;
	char	*m;
	int		nb;
	int		i;

	m = s;
	nb = 0;
	while (*s && ft_isspace(*s))
		++s;
	while (*s)
	{
		i = 0;
		if (ft_isspace(*s) && *(s - 1) && !ft_isspace(*(s - 1))
			&& !(*s = 0) && ++s)
			nb++;
		else if ((*s == '\'' || *s == '\"') && (i = ft_dodge_quote(s, i)))
			s += i;
		else
			++s;
	}
	nb += *(s - 1) && !ft_isspace(*(s - 1)) ? 1 : 0;
	if (!(t = (char **)ft_memalloc(sizeof(char *) * (nb + 1))))
		return (NULL);
	return (sft_tabdup(t, m, nb));
}

/*
**When opening pattern like \' or \" is meeted, returns index of cmd wich matchs
**with closing patterns.
*/

int			ft_dodge_quote(char *cmd, size_t i)
{
	char	c;

	c = cmd[i];
	while (cmd[++i] != c && cmd[i])
		if (cmd[i] == '\\')
			++i;
	return (cmd[i] ? i + 1 : i);
}

t_list		*ft_av_handle(char *cmd, size_t i)
{
	char	**t;
	char	c[2];
	t_list	*new;

	c[0] = cmd[i];
	c[1] = 0;
	cmd[i] = 0;
	if ((!cmd || !(t = ft_strdodgesplit(cmd)))
		&& ft_error(SHNAME, PARSE_ERR, c, CR_ERROR))
		return (NULL);
	cmd[i] = c[0];
	if (!(new = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	new->data = (void*)t;
	return (new);
}
