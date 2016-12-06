/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 16:28:45 by tboos             #+#    #+#             */
/*   Updated: 2016/03/28 16:29:29 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCLIST_H
# define DCLIST_H
# include <stdlib.h>

typedef struct		s_dclist
{
	void			*data;
	size_t			data_size;
	struct s_dclist	*next;
	struct s_dclist	*prev;
}					t_dclist;

void				ft_sorted_dclist_merge(t_dclist **begin1, t_dclist *begin2,
						int (*cmp)());
void				ft_sorted_dclist_insert(t_dclist **begin_list,
						t_dclist *new, int (*cmp)());
void				ft_dclstiter_if(t_dclist *begin_list, void (*f)(void *),
						void *data_ref, int (*cmp)());
void				ft_dclist_sort(t_dclist **begin_list, int (*cmp)());
size_t				ft_dclist_size(t_dclist *begin_list);
void				ft_dclist_reverse(t_dclist **begin_list);
void				ft_dclist_remove_if(t_dclist **begin_list, void *data_ref,
						int (*cmp)(), void (*ft_free)());
void				ft_dclist_push_front(t_dclist **begin_list, void *data,
						size_t data_size);
void				ft_dclist_push_back(t_dclist **begin_list, void *data,
						size_t data_size);
void				ft_dclist_merge(t_dclist **begin_list1,
						t_dclist *begin_list2);
t_dclist			*ft_dclist_last(t_dclist *begin_list);
t_dclist			*ft_dclist_find(t_dclist *begin_list, void *data_ref,
						int (*cmp)());
t_dclist			*ft_dclist_at(t_dclist *begin_list, unsigned int nbr);
t_dclist			*ft_dclstnew(void *content, size_t content_size);
void				ft_dclstdelone(t_dclist **alst,
						void (*del)(void *, size_t));
void				ft_dclstdel(t_dclist **alst, void (*del)(void *, size_t));
int					ft_dclstdel_err(t_dclist **alst,
						void (*del)(void *, size_t));
void				ft_dclstiter(t_dclist *lst, void (*f)(t_dclist *elem));
t_dclist			*ft_dclstmap(t_dclist *lst,
						t_dclist *(*f)(t_dclist *elem));

#endif
