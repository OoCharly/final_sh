# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tboos <marvin@42.fr>                       +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2015/11/04 18:24:51 by tboos             #+#    #+#             #
#*   Updated: 2016/09/21 11:10:11 by rbaran           ###   ########.fr       *#
#                                                                            #
# ************************************************************************** #
.PHONY: mrproper
.SUFFIXES:
NAME = libft.a
FLAGS = -Wall -Wextra -Werror
SRC = ft_atoi.c ft_exit.c ft_itoa.c ft_putchar.c ft_putchar_fd.c ft_putcstr.c \
	ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
	ft_putstr_fd.c ft_status.c ft_usage.c ft_putstrtab.c ft_inserttab.c\
	gnl/get_next_line.c ft_putstrlist.c ft_getenv.c ft_ringbell.c
LIST = ft_list_at.c ft_list_find.c ft_list_last.c ft_list_merge.c \
	ft_list_push_back.c ft_list_push_front.c ft_list_remove_if.c \
	ft_list_reverse.c ft_list_size.c ft_list_sort.c ft_lstdel.c \
	ft_lstdelone.c ft_lstiter.c ft_lstiter_if.c ft_lstmap.c ft_lstnew.c \
	ft_sorted_list_insert.c ft_sorted_list_merge.c ft_list_str.c \
	ft_list_strtab.c
LISTS = $(foreach L, $(LIST), list/$(L))
BASIC = ft_bzero.c ft_freegiveone.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
	ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_strcat.c \
	ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
	ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
	ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
	ft_strslashjoin.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtabdup.c \
	ft_strtabfind.c ft_strtabfree.c ft_strtrim.c ft_tolower.c ft_toupper.c \
	ft_strtabadd.c ft_strtabdiv.c ft_strtabiter.c ft_strinsert.c ft_isspace.c \
	ft_strtabjoin.c ft_strlenc.c ft_strfjoin.c ft_char_clean.c ft_strchrsed.c\
	ft_swap.c
BASICS = $(foreach B, $(BASIC), basics/$(B))
SRCS = $(SRC) $(LISTS) $(BASICS)
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

%.o: %.c
	gcc $(FLAGS) -c $^ -I includes -o $@

clean:
	rm -f $(OBJ)

fclean: mrproper

re: fclean all

mrproper: clean
	rm -f $(NAME)
