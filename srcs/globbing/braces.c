/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmunoz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:39:35 by jmunoz            #+#    #+#             */
/*   Updated: 2017/01/05 14:45:07 by jmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** For each list element, concatenate the current character of the string.
*/

static void		ft_catlist(t_list **arg, char *str, size_t size)
{
	t_list *list;

	if (!*arg)
		*arg = ft_lstnew(ft_strnew(BRACES_SIZE), 1);
	list = *arg;
	while (list)
	{
		list->data = ft_strncat(list->data, str, size);
		list = list->next;
	}
}

/*
** Take two lists. Build a third joining elements of the first and second.
** Free the first and second list.
*/

static t_list	*ft_distriblist(t_list *l1, t_list *list2)
{
	t_list	*list3;
	t_list	*l;
	t_list	*kill1;
	t_list	*kill2;
	char	*new;

	kill1 = l1;
	kill2 = list2;
	list3 = NULL;
	if (!l1)
		return (list2);
	while (l1)
	{
		l = list2;
		while (l)
		{
			new = ft_strcat(ft_strcpy(ft_strnew(BRACES_SIZE),l1->data),l->data);
			ft_list_push_back(&list3, ft_lstnew(new, 1));
			l = l->next;
		}
		l1 = l1->next;
	}
	ft_lstdel(&kill1, &ft_list_free_data);
	ft_lstdel(&kill2, &ft_list_free_data);
	return (list3);
}

/*
** cf ft_braces.
*/

void			ft_braces2(t_brace *b, char *str)
{
	b->arg2 = ft_braces(ft_strncpy(b->sub, str + 1, b->size - 1), 0);
	b->arg1 = (b->arg1) ? ft_distriblist(b->arg1, b->arg2) : b->arg2;
	ft_bzero(b->sub, BRACES_SIZE);
}

/*
** Checks char by char if we enter new braces and call again function in that
** case. Merge argument lists. Concatenate parts of an argument.
*/

t_list			*ft_braces(char *str, char out)
{
	t_brace		b;

	ft_bzero(&b, sizeof(t_brace));
	while (*str)
	{
		if (*str == '\\')
			ft_catlist(&(b.arg1), str++, 2);
		else if ((*str == '\'' || *str == '\"') && (b.jump = ft_dodge_quote(str, 0)))
		{
			ft_catlist(&(b.arg1), str, b.jump);
			str += b.jump - 1;
		}
		else if (*str == ',' && !out)
		{
			ft_list_merge(&(b.all), b.arg1);
			b.arg1 = NULL;
		}
		else if (*str == '{' && (b.size = ft_closechar(str, "{}")))
		{
			ft_braces2(&b, str);
			str += b.size;
		}
		else
			ft_catlist(&(b.arg1), str, 1);
		str++;
	}
	ft_list_merge(&(b.all), b.arg1);
	return (b.all);
}

/*
** Launch a first occurence of ft_braces with out = 1 (the it will take 0 value)
** Put list result into a char string. Free list and list data.
*/

char			**ft_launchbraces(char *str)
{
	t_list	*begin;
	t_list	*tmp;
	char	**result;

	result = NULL;
	if (str && (begin = ft_braces(str, 1)))
	{
		while (begin)
		{
			result = ft_strtabadd_free(result, begin->data);
			tmp = begin;
			begin = begin->next;
			ft_lstdelone(&tmp, NULL);
		}
	}
	return (result);
}
