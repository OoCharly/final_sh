/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_sentence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:15:11 by tboos             #+#    #+#             */
/*   Updated: 2016/11/18 14:15:15 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_build_sshell_sentence(t_list *begin, t_config *config)
{
	char	*tmp;
	char	*tocpy;
	char	*memo;

	memo = config->fg_sentence;
	config->fg_sentence = NULL;
	if (!(ft_build_sentence(begin, config)))
		return (NULL);
	tmp = config->fg_sentence;
	config->fg_sentence = memo;
	if (!(tocpy = ft_strnew(ft_strlen(tmp) + 4))
			&& ft_freegiveone((void**)&tmp))
		return (NULL);
	ft_strcpy(tocpy, "( ");
	ft_strcpy(tocpy + 2, tmp);
	ft_strcat(tocpy, " )");
	ft_freegiveone((void**)&tmp);
	return (tocpy);
}

int			ft_build_sentence(t_list *begin, t_config *config)
{
	char	*tmp;
	char	*tocpy;

	while (begin)
	{
		tocpy = NULL;
		if (!begin->data_size)
			tocpy = ft_strtabchrjoin((char **)begin->data, ' ');
		else if (begin->data_size == SSHELL)
			tocpy = ft_build_sshell_sentence(begin->data, config);
		else
			tocpy = ft_strdup((char *)begin->data);
		if (!tocpy && ft_freegiveone((void**)&config->fg_sentence))
			return (0);
		if (config->fg_sentence)
			tmp = ft_strchrjoin(config->fg_sentence, ' ', tocpy);
		else
			tmp = ft_strdup(tocpy);
		ft_freegiveone((void **)&config->fg_sentence);
		ft_freegiveone((void **)&tocpy);
		config->fg_sentence = tmp;
		begin = begin->next;
	}
	return (1);
}
