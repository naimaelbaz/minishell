# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 18:39:13 by nel-baz           #+#    #+#              #
#    Updated: 2023/06/04 13:24:20 by nel-baz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g 

FLAGS = -Wall -Werror -Wextra

SRCS =	main.c \
		lexing/lexing.c \
		lexing/lexing_utils.c \
		lexing/garbage_collector.c

OBJS = $(SRCS:.c=.o)

%.o: %.c minishell.h libft/libft.h
	$(CC) $(FLAGS) -c $< -o $@

all : libft $(NAME)	

libft :
	make -s -C libft all
$(NAME):  $(OBJS)
	$(CC) $(FLAGS) libft/libft.a -lreadline -L/Users/nel-baz/.brew/opt/readline/lib -I/Users/nel-baz/.brew/opt/readline/include $(OBJS) -o $(NAME)

clean:	
	rm -rf $(OBJS)
	make -s -C libft clean

fclean:	clean
	rm -rf $(NAME)
	make -s -C libft fclean

re : fclean all

.PHONY : all fclean clean re libft