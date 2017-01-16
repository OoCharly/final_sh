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

static char	**ft_function_split(char *name, char *p)
{
	char	**result;
	char	c;

	*p = 0;
	if ((!(result = (char**)ft_memalloc(sizeof(char*)))
		|| !(result = ft_strtabadd(result, ft_strjoin(name, "()"))))
		&& ft_error(SHNAME, "lexer", "malloc error", CR_ERROR | EEXIT))
		return (NULL);
	*p = '(';
	p += ft_gonext_par(p, 0);
	while (*p && *p != '{')
		++p;
	name = p;
	p += ft_gonext_par(p, 0);
	c = *p;
	*p = 0;
	if (!(result = ft_strtabadd(result, ft_strdup(name)))
		&& ft_error(SHNAME, "lexer", "malloc error", CR_ERROR | EEXIT))
		return (NULL);
	*p = c;
	return (*p ? ft_strtabjoin(result, ft_strdodgesplit(p)) : result);
}

/*
**Fills t with any words meets in m.
*/

static char	**sft_tabdup(char **t, char *m, int nb, int i)
{
	while (t && nb--)
	{
		if (!(t[i++] = ft_strdup(m)))
		{
			ft_error(SHNAME, "lexer", "malloc error", CR_ERROR | EEXIT);
			ft_strtabfree(t);
			return (NULL);
		}
		if (nb)
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
		else if (*s == '(' && nb && ft_test_emptyness(s, 1, ')')
			&& ft_error(SHNAME, NULL, FN_SPA_ERR, CR_ERROR | EEXIT))
			return (NULL);
		else if (*s == '(' && ft_test_emptyness(s, 1, ')'))
			return (ft_function_split(m, s));
		else if ((i = ft_increm_dodge_quotes(s, i)))
			s += i;
	}
	nb += *(s - 1) && !ft_isspace(*(s - 1)) ? 1 : 0;
	return (sft_tabdup(ft_memalloc(sizeof(char*) * (nb + 1)), m, nb, 0));
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
	if (!cmd || !(t = ft_strdodgesplit(cmd)))
		return (NULL);
	cmd[i] = c[0];
	if (!(new = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	new->data = (void*)t;
	return (new);
}
