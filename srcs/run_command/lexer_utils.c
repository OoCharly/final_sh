#include "minishell.h"

int			ft_test_emptyness(char *cmd, size_t i, char c)
{
	while (ft_isspace(cmd[i]))
		++i;
	if (cmd[i] == c)
		return (1);
	return (0);
}

size_t		ft_increm_dodge_quotes(char *cmd, size_t i)
{
	if (cmd[i] == '\\')
		i += 2;
	else if (cmd[i] == '\'' || cmd[i] == '\"')
		i = ft_dodge_quote(cmd, i);
	else
		++i;
	return (i);
}

size_t		ft_gonext_par(char *cmd, size_t i)
{
	int		par;
	char	c;

	par = 1;
	c = cmd[i];
	++i;
	while (cmd[i] && par != 0)
	{
		if (cmd[i] == c)
			++par;
		else if (c == '(' && cmd[i] == ')')
			--par;
		else if (c == '{' && cmd[i] == '}')
			--par;
		i = ft_increm_dodge_quotes(cmd, i);
	}
	return (i);
}
