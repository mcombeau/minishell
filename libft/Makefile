# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 13:48:30 by mcombeau          #+#    #+#              #
#    Updated: 2022/09/25 14:50:00 by mcombeau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
AR = ar rcs
SRC = ft_isalpha \
	ft_isdigit \
	ft_isalnum \
	ft_isascii \
	ft_isprint \
	ft_isspace \
	ft_strlen \
	ft_memset \
	ft_bzero \
	ft_memcpy \
	ft_memmove \
	ft_strlcpy \
	ft_strlcat \
	ft_toupper \
	ft_tolower \
	ft_strchr \
	ft_strrchr \
	ft_strncmp \
	ft_strcmp \
	ft_memchr \
	ft_memcmp \
	ft_strnstr \
	ft_atoi \
	ft_calloc \
	ft_strdup \
	ft_substr \
	ft_strjoin \
	ft_strtrim \
	ft_split \
	ft_itoa \
	ft_strmapi \
	ft_striteri \
	ft_putchar_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr_fd
BONUS_SRC = ft_lstnew \
	ft_lstadd_front \
	ft_lstsize \
	ft_lstlast \
	ft_lstadd_back \
	ft_lstdelone \
	ft_lstclear \
	ft_lstiter \
	ft_lstmap  

SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))
BONUS_SRCS = $(addsuffix .c, $(BONUS_SRC))
BONUS_OBJS = $(addsuffix .o, $(BONUS_SRC))

.c.o: $(SRCS) $(BONUS_SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $^

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re bonus
