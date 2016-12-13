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

#ifndef LIST_H
# define LIST_H
# include <stdlib.h>

typedef struct		s_list
{
	void			*data;
	size_t			data_size;
	struct s_list	*next;
}					t_list;

void				ft_sorted_list_merge(t_list **begin1, t_list *begin2,
						int (*cmp)());
void				ft_sorted_list_insert(t_list **begin_list, t_list *new,
						int (*cmp)());
void				ft_lstiter_if(t_list *begin_list, void (*f)(void *),
						void *data_ref, int (*cmp)());
void				ft_list_sort(t_list **begin_list, int (*cmp)());
size_t				ft_list_size(t_list *begin_list);
void				ft_list_reverse(t_list **begin_list);
void				ft_list_remove_if(t_list **begin_list, void *data_ref,
						int (*cmp)(), void (*ft_free)());
void				ft_list_push_front(t_list **begin_list, t_list *elem);
void				ft_list_push_back(t_list **begin_list, t_list *elem);
void				ft_list_merge(t_list **begin_list1, t_list *begin_list2);
t_list				*ft_list_last(t_list *begin_list);
t_list				*ft_list_find(t_list *begin_list, void *data_ref,
						int (*cmp)());
t_list				*ft_list_at(t_list *begin_list, unsigned int nbr);
t_list				*ft_lstnew(void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_list_free_data(void *data, size_t data_size);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
int					ft_lstdel_err(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t				ft_list_strlen(t_list *begin);
char				**ft_list_strtab(t_list *begin);
void				ft_list_free(void *data, size_t data_size);

#endif
