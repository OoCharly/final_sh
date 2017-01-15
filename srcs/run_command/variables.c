#include "minishell.h"

static int	ft_prep_var(char **argv, char *def, t_config *config)
{
	int		size;
	char	*arrow;

	size = 1;
	if (*def == '=')
	{
		*def = 0;
		++def;
		if (*def == '(')
			{
				def++;
				arrow = def;
				while (*arrow != ')')
					++arrow;
				*arrow = 0;
				ft_new_var(ft_strdup(*argv), ft_strdodgesplit(def),
					VAR_TAB, config);
			}
		else
			ft_new_var(ft_strdup(*argv), ft_strdup(def), VAR_STD, config);
	}
//	else
//	{
//		while (ft_isspace(*(--def))
//			;
//		*(++def) = 0;
//		while (*(++def) && *def != '{')
//			;
//		size = ft_tab_var_prep(*argv);
//
//	}
	return (size);
}

int			ft_is_only_variable(char ***argv, t_config *config)
{
	char	*match;
	int		size;

	while (*argv && **argv && (match = ft_strchr(**argv, '=')))
//		|| (match = ft_strchr((*argv)[0], '(')))
	{
		size = ft_prep_var(*argv, match + 1, config);
		while (size-- && (*argv = ft_strncmptabdel(*argv, **argv)))
			;
	}
	if (!*argv || (!**argv && FREE((void**)*argv)))
		return (1);
	return (0);
}
