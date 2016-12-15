int		ft_cleancmd(char *str)
{
	char	tok;

	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			tok = *str;
			ft_memmove(str, str + 1, ft_strlen(str));
			while (*str && *str != tok)
			{
				if (*str == '\\')
					ft_memmove(str, str + 1, ft_strlen(str));
				str++;
			}
			ft_memmove(str, str + 1, ft_strlen(str));
		}
		if (*str == '\\')
			ft_memmove(str, str + 1, ft_strlen(str));
		str++;
	}
	return (1);
}
