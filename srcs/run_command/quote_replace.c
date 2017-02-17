/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 09:21:44 by tboos             #+#    #+#             */
/*   Updated: 2017/02/17 15:13:36 by maxpetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Replace wildcards '~' and '$' in *str by env variables.
** Return NULL if malloc error.
*/

char	*ft_quotehandle(char **str, t_config *config)
{
	size_t		j;

	j = 0;
	while ((*str)[j])
	{
		if (((*str)[j] == '~' || (*str)[j] == '$')
				&& !(*str = ft_envvarinsert(*str, &j, config)))
			return (NULL);
		else if ((*str)[j] == '\'')
			j = ft_dodge_quote(*str, j);
		else if ((*str)[j] == '\\')
			j += 2;
		else
			++j;
	}
	return (*str);
}
