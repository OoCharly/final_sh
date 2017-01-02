#include "libft.h"

void	ft_strchrsed(char *str, char o, char d)
{
	while (str && *str)
	{
		if (*str == o)
			*str = d;
		++str;
	}
}
