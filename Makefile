# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 18:39:13 by nel-baz           #+#    #+#              #
#    Updated: 2023/07/12 18:08:40 by ylachhab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g

FLAGS = -Wall -Werror -Wextra -g -fsanitize=address

SRCS =	main.c \
		syntax_error/func_utils.c \
		syntax_error/func_utils1.c \
		syntax_error/func_utils2.c \
		lexing/lexing.c \
		lexing/lexing_utils.c \
		lexing/lexing_utils1.c \
		lexing/garbage_collector.c \
		expanding/expanding.c \
		expanding/expanding_utils.c \
		expanding/get_env.c \
		parcer/delete.c \
		parcer/parcer.c \
		parcer/parcer_utils.c \
		parcer/parcer_utils1.c \
		parcer/parcer_utils2.c \
		parcer/parcer_utils3.c \
		builtins/built.c \
		builtins/built1.c \
		builtins/export.c \
		builtins/export_utils.c \
		builtins/export_utils1.c \
		builtins/unset.c \
		builtins/cd.c \
		builtins/cd_utils.c \
		builtins/exit.c \
		execution/ft_check_path.c \
		execution/ft_check_path_utils.c


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
