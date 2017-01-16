#include "minishell.h"

static int	ft_prep_tab_var(char **argv, char *def, int size, t_config *config)
{
	char	**value;
	char	*mem;
	int		i;

	i = 0;
	value = NULL;
	while (argv[i] && (mem = def))
	{
		if (*def && *def != ')')
		{
			if ((def = ft_strchr(def, ')')))
				*def = 0;
			value = ft_strtabadd_free(value, ft_strdup(def));
			if (!*def)
				break ;
			++i;
			def = argv[i];
		}
		else if (def && *def == ')')
			break ;
	}
	ft_new_var(ft_strdup(*argv), value, VAR_TAB, config);
	return (size + i);
}

static int	ft_prep_var(char **argv, char *def, t_config *config)
{
	int		size;

	size = 1;
	if (*def == '=')
	{
		*def = 0;
		++def;
		if (*def == '(')
			size = ft_prep_tab_var(argv, def + 1, size, config);
		else
			ft_new_var(ft_strdup(*argv), ft_strdup(def), VAR_STD, config);
	}
	else
	{
		*def = 0;
		ft_new_var(ft_strdup(*argv), ft_strdup(argv[1]), VAR_FUN, config);
		++size;
	}
	return (size);
}

int			ft_is_only_variable(char ***argv, t_config *config)
{
	char	*match;
	int		size;

	while (*argv && **argv && ((match = ft_strchr(**argv, '='))
		|| (match = ft_strchr((*argv)[0], '(')))
		&& (size = ft_prep_var(*argv, match, config)))
		while (size-- && (*argv = ft_strncmptabdel(*argv, **argv)))
			;
	if (!*argv || (!**argv && FREE((void**)*argv)))
		return (1);
	return (0);
}
