/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:39:59 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/08 21:30:46 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirection(t_enum *enu, char **input_line, t_free **ptr,
						t_token **token)
{
	if (**input_line == RED_IN && *(*input_line + 1) == RED_IN)
	{
		enu->type = RED_IN;
		add_back(token, ft_new(*input_line, 2, *enu, ptr));
		return ((*input_line) += 2, 1);
	}
	else if (**input_line == RED_OUT && *(*input_line + 1) == RED_OUT)
	{
		enu->type = RED_OUT;
		add_back(token, ft_new(*input_line, 2, *enu, ptr));
		return ((*input_line) += 2, 1);
	}
	else if (**input_line == RED_IN)
	{
		enu->type = RED_IN;
		add_back(token, ft_new(*input_line, 1, *enu, ptr));
		return ((*input_line)++, 1);
	}
	else if (**input_line == RED_OUT)
	{
		enu->type = RED_OUT;
		add_back(token, ft_new(*input_line, 1, *enu, ptr));
		return ((*input_line)++, 1);
	}
	return (0);
}

int	ft_pipe_space(t_enum *enu, char **input_line, t_free **ptr,
						t_token **token)
{
	if (**input_line == WHITE_SPACE)
	{
		enu->type = WHITE_SPACE;
		add_back(token, ft_new(*input_line, 1, *enu, ptr));
		while (*(*input_line + 1) == WHITE_SPACE)
			(*input_line)++;
		return ((*input_line)++, 1);
	}
	else if (**input_line == PIPE)
	{
		enu->type = PIPE;
		add_back(token, ft_new(*input_line, 1, *enu, ptr));
		return ((*input_line)++, 1);
	}
	return (0);
}

t_token	*ft_new(char *input_line, int len, t_enum enu, t_free **ptr)
{
	t_token	*node;

	node = ft_malloc(ptr, sizeof(t_token));
	if (!node)
		return (NULL);
	node->data = ft_substr(input_line, 0, len);
	ft_add_to_free(ptr, ft_new_node(node->data));
	node->type = enu.type;
	node->state = enu.state;
	node->next = NULL;
	return (node);
}

void	add_back(t_token **token, t_token *new)
{
	t_token	*ptr;

	ptr = *token;
	if (!ptr)
	{
		*token = new;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

int	ft_is_special(char c)
{
	if (c == '*' || c == '?' || c == '-' || c == '@'
		|| c == '#' || c == '!')
		return (1);
	return (0);
}

int	get_len_of_var(char *input_line, int i)
{
	if (ft_is_special(input_line[i]))
		return (2);
	while (input_line[i] && (ft_isalnum(input_line[i]) || input_line[i] == '_')
		&& input_line[i] != WHITE_SPACE && input_line[i] != PIPE
		&& input_line[i] != RED_IN && input_line[i] != RED_OUT
		&& input_line[i] != D_QOUTE && input_line[i] != QOUTE
		&& input_line[i] != ENV_VAR)
		i++;
	return (i);
}

int	get_len_of_word(char *input_line, int i)
{
	while (input_line[i]
		&& input_line[i] != WHITE_SPACE && input_line[i] != PIPE
		&& input_line[i] != RED_IN && input_line[i] != RED_OUT
		&& input_line[i] != D_QOUTE && input_line[i] != QOUTE
		&& input_line[i] != ENV_VAR)
		i++;
	return (i);
}

int	ft_get_length(char *input_line)
{
	int	i;

	i = 0;
	if (input_line[i] == D_QOUTE)
	{
		while (input_line[i] && input_line[i + 1] != D_QOUTE)
			i++;
		return (i + 2);
	}
	else if (input_line[i] == QOUTE)
	{
		while (input_line[i] && input_line[i + 1] != QOUTE)
			i++;
		return (i + 2);
	}
	else if (input_line[i] == ENV_VAR)
		return (get_len_of_var(input_line, ++i));
	else
		return (get_len_of_word(input_line, i));
	return (0);
}

int	ft_check_line(char c)
{
	if ((!c || c == RED_IN || c == RED_OUT || c == WHITE_SPACE
			|| c == PIPE))
		return (1);
	return (0);
}

int	ft_env_variable(t_enum *enu, char **input_line, t_free **ptr,
						t_token **token)
{
	int	len;

	if (**input_line == ENV_VAR)
	{
		if (ft_check_line(*(*input_line + 1)))
		{
			enu->state = DOLLAR_SIGN;
			enu->type = WORD;
			add_back(token, ft_new(*input_line, 1, *enu, ptr));
			return ((*input_line)++, 1);
		}
		else
		{
			if ((*(*input_line + 1) == D_QOUTE || *(*input_line + 1) == QOUTE))
				(*input_line)++;
			len = 2;
			if (*(*input_line + 1) != ENV_VAR)
				len = ft_get_length(*input_line);
			enu->state = DOLLAR_SIGN;
			enu->type = WORD;
			add_back(token, ft_new(*input_line, len, *enu, ptr));
			return ((*input_line) += len, 1);
		}
	}
	return (0);
}

int	ft_qoute(t_enum *enu, char **input_line, t_free **ptr,
			t_token **token)
{
	int	len;

	if (**input_line == QOUTE || **input_line == D_QOUTE)
	{
		len = ft_get_length(*input_line);
		if (**input_line == QOUTE)
			enu->state = IN_QOUTE;
		else if (**input_line == D_QOUTE)
			enu->state = IN_D_QOUTE;
		enu->type = WORD;
		add_back(token, ft_new(*input_line, len, *enu, ptr));
		(*input_line) += len;
		return (1);
	}
	return (0);
}

void	ft_lexing(char *input_line, t_token	**token, t_free	**ptr)
{
	t_enum	enu;
	int		len;

	while (*input_line)
	{
		enu.state = GENERAL;
		if (ft_redirection(&enu, &input_line, ptr, token))
			continue ;
		else if (ft_pipe_space(&enu, &input_line, ptr, token))
			continue ;
		else if (ft_qoute(&enu, &input_line, ptr, token))
			continue ;
		else if (ft_env_variable(&enu, &input_line, ptr, token))
			continue ;
		else
		{
			len = ft_get_length(input_line);
			enu.type = WORD;
			add_back(token, ft_new(input_line, len, enu, ptr));
			input_line += len;
		}
	}
}
