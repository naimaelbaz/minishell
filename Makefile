# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 18:39:13 by nel-baz           #+#    #+#              #
#    Updated: 2023/06/10 10:34:21 by ylachhab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g

FLAGS = -Wall -Werror -Wextra

SRCS =	main.c \
		syntax_error/func_utils.c \
		syntax_error/func_utils1.c \
		lexing/lexing.c \
		lexing/lexing_utils.c \
		lexing/lexing_utils1.c \
		lexing/garbage_collector.c \
		expanding/expanding.c \
		expanding/expanding_utils.c \
		expanding/get_env.c \
		parcer/delete.c

OBJS = $(SRCS:.c=.o)

%.o: %.c minishell.h libft/libft.h
	$(CC) $(FLAGS) -c $< -o $@

all : libft $(NAME)

libft :
	make -s -C libft all bonus

$(NAME):  $(OBJS)
	$(CC) $(FLAGS) libft/libft.a -L/Users/ylachhab/.brew/opt/readline/lib -I/Users/ylachhab/.brew/opt/readline/include  -lreadline $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	make -s -C libft clean

fclean:	clean
	rm -rf $(NAME)
	make -s -C libft fclean

re : fclean all

.PHONY : libft
