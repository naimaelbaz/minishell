/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:30 by nel-baz           #+#    #+#             */
/*   Updated: 2023/06/04 17:58:43 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

enum e_state
{
	GENERAL,
	IN_D_QOUTE,
	IN_QOUTE,
};

enum e_type
{
	WORD = -1,
	WHITE_SPACE = 32,
	QOUTE = '\'',
	D_QOUTE = '\"',
	ENV_VAR = '$',
	PIPE = '|',
	RED_IN = '<',
	RED_OUT = '>',
	RED_APP_OUT,
	HERE_DOC,
};

typedef struct s_token
{
	char			*data;
	enum e_type		type;
	enum e_state	state;
	struct s_token	*next;
}	t_token;

typedef struct s_enum
{
	enum e_type		type;
	enum e_state	state;
}	t_enum;

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}	t_free;

// syntax_error_functions

int		ft_check_redirect_input(char *input);
int		ft_check_redirect_output(char *input);
int		ft_check_pipe(char *input);
int		ft_pipe_end(char *input);
int		ft_check_quote_close(char *input);
int		ft_check_syntax_error(char *input);

// lexing_functions

void	ft_lexing(char *input_line, t_token	**token, t_free **ptr);
void	ft_free(t_free **ptr);
void	*ft_malloc(t_free **ptr, int size);
void	ft_add_to_free(t_free **lst, t_free *new);
t_free	*ft_new_node(void *content);
int		ft_redirection(t_enum *enu, char **input_line, t_free **ptr,
			t_token **token);
t_token	*ft_new(char *input_line, int len, t_enum enu, t_free **ptr);
void	add_back(t_token **token, t_token *new);
int		ft_pipe_space(t_enum *enu, char **input_line, t_free **ptr,
			t_token **token);
int		ft_qoute(t_enum *enu, char **input_line, t_free **ptr,
			t_token **token);
int		ft_get_length(char *input_line);

#endif