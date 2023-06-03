# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 12:06:17 by ylachhab          #+#    #+#              #
#    Updated: 2022/11/10 18:56:34 by ylachhab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = libft.a

FLAGS  = -Wall -Wextra -Werror

CC = cc

AR = ar rc

RM = rm -f

SRCS  = ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c
		
BSRCS = ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstlast.c ft_lstnew.c ft_lstsize.c\
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c  
		
OBJS = $(SRCS:.c=.o)

SOBJ = $(BSRCS:.c=.o)

all: $(NAME)

%.o: %.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus : all $(SOBJ)
	$(AR) $(NAME) $(SOBJ)
    
clean:
	$(RM) $(OBJS) $(SOBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all