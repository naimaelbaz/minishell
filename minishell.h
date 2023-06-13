/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:30 by nel-baz           #+#    #+#             */
/*   Updated: 2023/06/13 19:27:11 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

# include "./libft/libft.h"

enum e_state
{
	GENERAL,
	IN_D_QOUTE,
	IN_QOUTE,
	DOLLAR_SIGN,
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

//tokenaizer linked_list

typedef struct s_token
{
	char			*data;
	enum e_type		type;
	enum e_state	state;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//struct of enums

typedef struct s_enum
{
	enum e_type		type;
	enum e_state	state;
}	t_enum;

//garbage collector

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}	t_free;

//struct of expanding variables

typedef struct s_expand
{
	char			*key;
	char			*value;
	struct s_expand	*next;
}	t_expand;

//

typedef struct s_cmd
{
	char			*cmd;
	int				input;
	int				output;
	char			**arg;
	struct s_cmd	*next;
}	t_cmd;

// syntax_error_functions in folder syntax_error

int			ft_check_redirect_input(char *input);
int			ft_check_redirect_output(char *input);
int			ft_check_pipe(char *input);
int			ft_pipe_first(char *input);
int			ft_check_quote_close(char *input);
int			ft_check_syntax_error(char *input);
int			ft_check_in_quote(char *input, int i);

// garbadge_collector in folder lexing

void		ft_free(t_free **ptr);
void		ft_add_to_free(t_free **lst, t_free *new);
t_free		*ft_new_node(void *content);
void		*ft_malloc(t_free **ptr, int size);

// lexing_functions in folder lexing

void		ft_lexing(char *input_line, t_token	**token, t_free **ptr);
int			ft_redirection(t_enum *enu, char **input_line, t_free **ptr,
				t_token **token);
t_token		*ft_new(char *input_line, int len, t_enum enu, t_free **ptr);
void		add_back(t_token **token, t_token *new);
int			ft_pipe_space(t_enum *enu, char **input_line, t_free **ptr,
				t_token **token);
int			ft_qoute(t_enum *enu, char **input_line, t_free **ptr,
				t_token **token);
int			ft_env_variable(t_enum *enu, char **input_line, t_free **ptr,
				t_token **token);
int			ft_is_special(char c);
int			ft_check_line(char c);
int			ft_get_length(char *input_line);

// expanding variables in folder expanding

char		*ft_strcpy(char *dest, char *src);
int			ft_strcmp(char *s1, char *s2);
char		*ft_get_value(char *sub, t_expand *expand, int a);
int			ft_is_spec(char c);
t_expand	*ft_get_env(t_free **ptr, char **env);
void		ft_expanding(t_token **token, t_expand *expand, t_free **ptr);
char		*ft_split_expand(char *s, t_expand *expand);
int			ft_is_enum(char c);

// delete in folder parcer

void		ft_delete(t_token **token, t_free **ptr);
void		ft_join_string(t_token **token);
void		ft_parcer(t_token *token, t_cmd **cmd, t_free **ptr);
char		*ft_get_arg(t_token *token, t_free **ptr);
char		*ft_get_cmd(t_token *tmp);
int			ft_count_pipe(t_token *token);
void		ft_open_pipe(t_cmd **cmd);
//to test
int			ft_get_len(t_token *token);
char 		**split_args(t_token	*token);
#endif