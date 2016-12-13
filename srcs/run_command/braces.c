<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:39:35 by jmunoz            #+#    #+#             */
/*   Updated: 2016/12/07 16:12:43 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_braces(char *arg)
{
	while (*arg)
	{
		if (*arg == '{'
=======
#include "minishell.h"

/*
** For each list element, concatenate the current character of the string.
*/

static void		ft_catlist(t_list **arg, char *str)
{
	t_list *list;

	if (!*arg)
		*arg = ft_lstnew(ft_strnew(SIZE), 0);
	list = *arg;
	while (list)
	{
		list->data = ft_strncat(list->data, str, 1);
		list = list->next;
	}
}

/*
** Take two lists. Build a third joining elements of the first and second.
** Free the first and second list.
*/

static t_list		*ft_distriblist(t_list *list1, t_list *list2)
{
	t_list	*list3;
	t_list	*l;
	t_list	*kill1;
	t_list	*kill2;

	kill1 = list1;
	kill2 = list2;
	list3 = NULL;
	if (!list1)
		return (list2);
	while (list1)
	{
		l = list2;
		while (l)
		{
			ft_list_push_back(&list3, ft_lstnew(ft_strjoin(list1->data, l->data), 0));
			l = l->next;
		}
		list1 =list1->next;
	}
	ft_lstdel(&kill1, &ft_list_free_data);
	ft_lstdel(&kill2, &ft_list_free_data);
	return (list3);
}

/*
 ** If the brace is closed later, return the index of closing brace.
 ** If not, return 0.
 */

int				ft_isbraces(char *str)
{
	int		open;
	int		close;
	int		i;

	open = 0;
	close = 0;
	i = -1;
	while (str[++i])
	{
		if ((!i && str[i] == '{') || (i && str[i] == '{' && str[i - 1] != '\\'))
			open++;
		if ((!i && str[i] == '}') || (i && str[i] == '}' && str[i - 1] != '\\'))
			close++;
		if (open == close)
			return (i);
	}
	return (0);
}

/*
** cf ft_braces.
*/

void	ft_braces2(t_brace *b, char *str)
{
	b->arg2 = ft_braces(ft_strncpy(b->sub, str + 1, b->size - 1), 0);
	b->arg1 = (b->arg1) ? ft_distriblist(b->arg1, b->arg2) : b->arg2;
	ft_bzero(b->sub, SIZE);
}

/*
** Checks char by char if we enter new braces and call again function in that
** case. Merge argument lists. Concatenate parts of an argument.
*/

t_list		*ft_braces(char *str, char out)
{
	t_brace		b;

	ft_bzero(&b, sizeof(t_brace));
	while (*str)
	{
		if (*str == '\\' && !b.jump)
			b.jump = 2;
		else if (*str == ',' && !out)
		{
			ft_list_merge(&(b.all), b.arg1);
			b.arg1 = NULL;
		}
		else if (*str == '{' && !b.jump && (b.size = ft_isbraces(str)))
		{
			ft_braces2(&b, str);
			str += b.size;
		}
		else
			ft_catlist(&(b.arg1), str);
		if (b.jump > 0)
			b.jump--;
		str++;
	}
	ft_list_merge(&(b.all), b.arg1);
	return (b.all);
}

char	*ft_launchbraces(char *str)
{
	t_list	*list;
	t_list	*tmp;
	char	*tot;

	list = NULL;
	tot = NULL;
	if (str && (list = ft_braces(str, 1)))
	{
		if (!(tot = ft_strnew(ft_size_list(list))))
			return (tot);
		while (list)
		{
		ft_strcat(ft_strcat(tot, list->data), " ");
		tmp  = list;
		list = list->next;
		ft_lstdelone(&tmp, ft_list_free_data);
		}
	}
	return (tot);
}
>>>>>>> b43df9ea471fcfc4a0ac2e673f185bc35f114f49
