#include <stdio.h>



int			ft_dochars(char arg, char chars, int *jump)
{
	if ((arg == '\\' ) && !*jump)
		(*jump)++;
	else if (arg == '\'' && !*jump)
		*jump += 2;
	else if (arg == '\"' && !*jump)
		*jump += 4;
	else if (arg == '\'' && *jump == 2)
		*jump -= 2;
	else if (arg == '\"' && *jump == 4)
		*jump -= 4;
	else if (arg == chars && !*jump)
		return (1);
	else if (*jump == 1)
		(*jump)--;
	return (0);
}

int			ft_checkchars(char *tmp, char	*chars)
{
	char	*arg;
	int		jump;

	while (*chars)
	{
		jump = 0;
		arg = tmp;
		while (*arg)
		{
			if (ft_dochars(*arg, *chars, &jump))
				return (1);
			arg++;
		}
		chars++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	if (ac > 1)
	{
		printf("received: %s\n", av[1]);
		if (ft_checkchars(av[1], "*[]?"))
			printf("VRAI\n");
	}
	return (0);
}
