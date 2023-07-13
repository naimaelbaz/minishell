/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:30 by nel-baz           #+#    #+#             */
/*   Updated: 2023/07/13 10:05:44 by ylachhab         ###   ########.fr       */
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
# include <sys/stat.h>
# include <limits.h>
# include <errno.h>

# include "./libft/libft.h"

# define HEREDOC "here_doc"

typedef struct s_global
{
	int		exit_global;
	int		shlvl;
	int		path;
	char	**split;
	char	*name_hedoc;
}	t_global;

extern t_global	g_global;

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
	struct s_expand	*prev;
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

//

typedef struct s_export
{
	int		i;
	int		j;
	int		nb;
	int		plus;
	char	*key;
	char	*val;
}	t_export;

typedef struct s_main
{
	t_token		*token;
	t_free		*ptr;
	t_free		*new_ptr;
	t_expand	*expand;
	t_cmd		*cmd;
}	t_main;

// syntax_error_functions in folder syntax_error

int			ft_check_redirect_input(char *input);
int			ft_check_redirect_output(char *input);
int			ft_check_pipe(char *input);
int			ft_pipe_first(char *input);
int			ft_check_quote_close(char *input);
int			ft_check_syntax_error(char *input);
int			ft_check_in_quote(char *input, int i);
int			ft_check_parenthesis(char *input);
int			ft_check_brackets(char *input);

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
t_expand	*ft_exp_new(char *env, t_free **ptr);
void		ft_exp_add_back(t_expand **lst, t_expand *new);
int			ft_strcmp(char *s1, char *s2);
char		*ft_get_value(char *sub, t_expand *expand, int a);
int			ft_is_spec(char c);
t_expand	*ft_get_env(t_free **ptr, char **env);
void		ft_expanding(t_token **token, t_expand *expand, t_free **ptr);
char		*ft_split_expand(char *s, t_expand *expand);
int			ft_is_enum(char c);
void		ft_exit_expand(char **head, t_free **ptr);

// delete in folder parcer

void		ft_delete(t_token **token, t_free **ptr);
void		ft_join_string(t_token **token, t_free **ptr);

//

char		**ft_get_arg(t_token *token, t_free **newptr);
void		ft_parcer(t_token *token, t_cmd **cmd, t_free **ptr,
				t_expand *expand);
void		ft_open_pipe(t_cmd **cmd);
char		*ft_join(char *s1, char *s2);

// parcer_utils in folder parcer

t_cmd		*ft_new_cmd(t_free **ptr, void *content);
void		ft_add_cmd(t_cmd **lst, t_cmd *new);
int			ft_count_pipe(t_token	*token);
char		*ft_get_cmd(t_token *tmp, t_free **ptr);
int			ft_len(t_token *token, t_free **newptr);

// parcer_utils1 in folder parcer

char		**ft_get_arg(t_token *token, t_free **newptr);
char		*check_existfile(void);
void		ft_expand_here_doc(char **str, t_expand *expand);
void		ft_expand_in_heredoc(char **input, t_expand	*expand);
void		ft_open_pipe(t_cmd **cmd);
void		ft_open_files(t_token **tmp, t_cmd **new, t_expand *expand, int *p);
void		ft_red_in(t_token **tmp, t_cmd **new, char **f);
void		ft_input_red(t_token **tmp, t_cmd **new,
				t_expand *expand, char **f);
int			ft_ambiguous(t_token **tmp, t_cmd **new);
int			ft_is_pipe(t_token **tmp, t_cmd **new, int	*p);
void		ft_unlink_heredoc(void);

// built in folder builtins

void		ft_execution(t_cmd *cmd, t_expand **expand, t_free **new_ptr,
				t_free **ptr);
void		ft_env(t_expand *expand, int i, char **arg);
void		ft_delete_empty_str(t_token **token);

void		ft_export(t_expand *expand, int i, t_free **ptr);
t_expand	*ft_add_export(t_expand *expand, char **arg, t_free **ptr);
void		ft_get_key(char *arg, t_export *export);
void		ft_get_key2(char *arg, t_export *export, t_free **ptr);
t_expand	*ft_export_new(char *key, char *val, t_free **ptr);
void		ft_print_error(char *arg);
int			ft_check_arg(char *key, char *val, t_expand **expand, int plus);
int			ft_check_syntax(char *key);
int			ft_check(char *arg, t_export *export, t_free **ptr);

int			ft_search(char **str);
void		ft_echo(int i, char **arg);
void		ft_pwd(int i);
t_expand	*ft_empty_env(t_free **ptr);

t_expand	*ft_unset(char	**arg, t_expand *expand);

t_expand	*ft_cd(t_expand *expand, char **arg, t_free **ptr);
char		*ft_search_val(char *key, t_expand	*expand);
void		ft_set_val(char *key, char *value, t_expand **expand);
void		ft_printf_error(char *arg);

void		ft_exit(char **args);

char		**ft_split_path(t_expand *expand);
void		to_be_executed(t_cmd *cmd, t_free **ptr,
				t_expand **expand, t_cmd *h);
int			ft_check_path(char *join);
char		*ft_found_path(char **split, char *cmd, t_free **ptr);
char		**myenv(t_expand *expand, t_free **ptr);

#endif