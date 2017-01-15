#include "minishell.h"

t_var	*var_name_cmp(void *data_list, void *name)
{
	return (ft_strcmp(((t_var*)data_list)->name, (char*)name));
}

int		new_var(char *name, void *value, size_t type, t_config *config)
{
	t_var	*new;
	t_list	*elem;

	if (!(new = (t_var*)ft_memalloc(sizeof(t_var)))
		&& ft_error(SHNAME, "export", "malloc error", CR_ERROR | SERROR))
		return (0);
	new->name = name;
	new->value = value;
	new->type = type;
	if (!(elem = ft_lstnew((void*)new, VAR))
		&& ft_error(SHNAME, "export", "malloc error", CR_ERROR | SERROR))
		return (0);
	ft_list_push_front(&begin->variables, elem);
	return (1);
}
