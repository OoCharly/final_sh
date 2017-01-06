#include "libft.h"

void	ft_strswap(char **s1, char **s2)
{
	char	*m;

	m = *s1;
	*s1 = *s2;
	*s2 = m;
}
