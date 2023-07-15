# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 18:39:13 by nel-baz           #+#    #+#              #
#    Updated: 2023/07/13 19:38:14 by ylachhab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

FLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

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

all : libft $(NAME)

libft :
	make -C ./libft all

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@


$(NAME):  $(OBJS)
	$(CC) $(FLAGS) $(OBJS) libft/libft.a -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include  -lreadline -o $(NAME)

clean:
	rm -rf $(OBJS)
	make  -C libft clean

fclean:	clean
	rm -rf $(NAME)
	make  -C libft fclean

re : fclean all

.PHONY : libft bonus
