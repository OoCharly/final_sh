#include "../includes/libft.h"

char	**ft_list_strtab(t_list	*begin)
{
	char	**tab;
	size_t	size;
	int		i;

	tab = NULL;
	if (begin)
	{
		size = ft_list_size(begin);
		if (!(tab = (char**)ft_memalloc(sizeof(void*) * (size + 1))))
			return (NULL);
		i = -1;
		while (++i < (int)size && begin)
		{
			tab[i] = begin->data;
			begin = begin->next;
		}
	}
	return (tab);
}

/*
int		main(int ac, char **av)
{
	char	test[] = "jordan";
	char	test1[] = "romain";
	char	test2[] = "theo";
	char	*test3;
	t_list	*begin;
	t_list	*tmp;
	char	**tab;

	test3 = NULL;
	tab = NULL;
	ft_list_push_back(&begin, ft_lstnew(test3, 1));
	ft_list_push_back(&begin, ft_lstnew(test1, 1));
	ft_list_push_back(&begin, ft_lstnew(test2, 1));
	ft_putendl("Impression de la liste");
	tmp = begin;
	while (begin)
	{
		ft_putendl(begin->data);
		begin = begin->next;
	}
	if (!(tab = ft_list_strtab(NULL)))
		ft_putendl("Echec du transfert de la liste en tableau");
	else
	{
		ft_putendl("Impression du tableau");
		ft_putstrtab(tab, '\n');
	}
	return (0);
}*/
