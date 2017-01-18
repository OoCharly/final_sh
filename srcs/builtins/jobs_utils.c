/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 08:35:03 by tboos             #+#    #+#             */
/*   Updated: 2017/01/18 15:48:02 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmp_jobs(t_list *s, char *description, int i)
{
	char	*sentence;

	if (!description)
		return (1);
	sentence = ((t_sentence*)s->data)->sentence;
	if (*description == '%' && ++description)
	{
		if (ft_isdigit(*description) && ft_atoi(description) == i)
			return (1);
		else if (ft_strstr(description, sentence))
			return (1);
	}
	else if (!ft_strncmp(description, sentence, ft_strlen(description)))
		return (1);
	return (0);
}

void	ft_print_jobs(t_list *sentence, char *description)
{
	static char	*desc = NULL;
	static char	found = 1;
	static int	i = 0;

	if (!sentence)
	{
		if (!found && desc)
			ft_error("jobs", desc, "no such job", CR_ERROR);
		ft_freegiveone((void**)&desc);
		i = 1;
		found = 0;
		if (description)
			desc = ft_strdup(description);
		return ;
	}
	if (ft_cmp_jobs(sentence, desc, i))
	{
		FT_PUTSTRFD("[", ft_st_itoa(i), "]       ", 1);
		FT_PUTSTRFD(ft_st_itoa(*((int*)sentence->next->data)), "    ",
				((t_sentence*)sentence)->state == RUNNING ?
										"Running" : "Suspended", 1);
		FT_PUTSTRFD("    ", ((t_sentence*)sentence->data)->sentence, "\n", 1);
		//printf("In jobs: state: %d\n", ((t_sentence*)sentence->data)->state);
		found = 1;
	}
	i++;
}
