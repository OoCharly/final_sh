#include "minishell.h"

int				var_name_cmp(void *data_list, void *name)
{
	return (ft_strcmp(((t_var*)data_list)->name, (char*)name));
}

int				ft_new_var(char *name, void *value, size_t type, t_config *config)
{
	t_var	*new;
	t_list	*elem;

	if (type == VAR_STD && 0 <= ft_igetenv(name, config->env))
		ft_setenv(name, value, config);
	else
	{
		if (!(new = (t_var*)ft_memalloc(sizeof(t_var)))
			&& ft_error(SHNAME, "export", "malloc error", CR_ERROR | SERROR))
			return (0);
		new->name = name;
		new->value = value;
		new->type = type;
		if ((elem = ft_list_find(config->variables, (void*)name, &var_name_cmp)))
		{
			ft_list_free_av(elem->data, elem->data_size);
			elem->data = new;
			elem->data_size = VAR;
		}
		else if (!(elem = ft_lstnew((void*)new, VAR)) && FREE((void**)&new)
			&& ft_error(SHNAME, "export", "malloc error", CR_ERROR | SERROR))
			return (0);
		else
			ft_list_push_front(&config->variables, elem);
	}
	return (1);
}

char			*ft_getvar(char	*name, t_config *config)
{
	t_list	*match;
	t_var	*v;

	if ((match = ft_list_find(config->variables, (void*)name, &var_name_cmp)))
	{
		v = (t_var*)match->data;
		if (v->type == VAR_TAB)
			return (v->value ? ((char**)v->value)[0] : NULL);
		else if (v->type == VAR_STD)
			return ((char*)v->value);
	}
	return (NULL);
}
