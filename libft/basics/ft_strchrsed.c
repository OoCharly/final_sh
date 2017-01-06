#include "libft.h"

void	ft_strchrsed(char *str, char origin, char target)
{
	while (str && *str)
	{
		if (*str == origin)
			*str = target;
		++str;
	}
}
