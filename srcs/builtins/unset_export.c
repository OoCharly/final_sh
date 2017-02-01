/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 14:19:49 by rbaran            #+#    #+#             */
/*   Updated: 2017/02/01 14:42:09 by rbaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_unset_with_flags(char **argv, t_config *config, int flags,
		int i)
{
	t_list	*match;
	t_var	*var;

	while (argv[i])
	{
		if ((match = ft_list_find(config->variables, (void*)argv[i],
						&var_name_cmp)))
		{
			var = (t_var*)match->data;
			if (!flags || (var->type == VAR_FUN && flags == 2)
					|| (flags == 1 && var->type != VAR_FUN))
			{
				ft_list_remove_if(&config->variables, (void*)argv[i],
						&var_name_cmp, &ft_list_free_elem);
			}
		}
		++i;
	}
}

void			ft_unset(char **argv, t_config *config)
{
	int		i;
	int		flags;
	char	*p;

	i = 0;
	while ((p = argv[++i]) && *p == '-')
		while (*(++p))
		{
			if (((*p == 'v' && flags == 2) || (*p == 'f' && flags == 1))
			&& ft_error(SHNAME, "unset", "wrong flags combinaison", CR_ERROR))
				return ;
			else if (*p == 'v' || *p == 'f')
				flags = *p == 'v' ? 1 : 2;
			else if (ft_error(SHNAME, "unset", "unknow flag", CR_ERROR))
				return ;
		}
	ft_unset_with_flags(argv, config, flags, i);
}

void			ft_export(char **argv, t_config *config)
{
	int		i;
	int		flags;
	char	*p;

	i = 0;
	flags = 0;
	while ((p = argv[++i]) && *p == '-')
		while (*(++p))
		{
			if (*p == 'p')
				flags = 1;
			else if (ft_error(SHNAME, "export", "unknow flag", CR_ERROR))
				return ;
		}
	while (argv[i])
	{
		if ((p = ft_strchr(argv[i], '=')))
			ft_prep_var(argv + i, p, config);
		else
			ft_new_var(ft_strdup(argv[i]), NULL, VAR_STD, config);
		++i;
	}
	if (flags)
		ft_lstiter(config->variables, &ft_print_list);
}
