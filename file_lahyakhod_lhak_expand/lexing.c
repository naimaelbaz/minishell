/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:53:55 by nel-baz           #+#    #+#             */
/*   Updated: 2023/06/07 19:44:29 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if ((input_line[i] == RED_IN && input_line[i + 1] == RED_IN)
		|| (input_line[i] == RED_OUT && input_line[i + 1] == RED_OUT))
		return (2);
	else if (input_line[i] == WHITE_SPACE || input_line[i] == PIPE
		|| input_line[i] == RED_IN || input_line[i] == RED_OUT)
		return (1);
	else if (input_line[i] == D_QOUTE)
	{
		while (input_line[i] && input_line[i + 1] != D_QOUTE)
			i++;
		return (i);
	}
	else if (input_line[i] == QOUTE)
	{
		while (input_line[i] && input_line[i + 1] != QOUTE)
			i++;
		return (i);
	}
	else if (input_line[i] == ENV_VAR)
	{
		i++;
		// if (!ft_isalpha(input_line[i]) && input_line[i] != '_')
		// 	return (1);
		while (input_line[i] && input_line[i] != ENV_VAR
			&& input_line[i] != WHITE_SPACE && input_line[i] != PIPE
			&& input_line[i] != RED_IN && input_line[i] != RED_OUT
			&& input_line[i] != D_QOUTE && input_line[i] != QOUTE)
			i++;
		return (i);
	}
	else
		return (get_len_of_word(input_line, i));
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

void	ft_lexing(char *input_line, t_token	**token, t_free	**ptr)
{
	int		len;
	t_enum	enu;

	while (*input_line)
	{
		enu.state = GENERAL;
		if (ft_redirection(&enu, &input_line, ptr, token))
			continue ;
		else if (ft_pipe_space(&enu, &input_line, ptr, token))
			continue ;
		else if (ft_qoute(&enu, &input_line, ptr, token))
			continue ;
		else if (*input_line == ENV_VAR)
		{
			len = ft_get_length(input_line);
			if (!ft_isalpha(*(input_line + 1)) && *(input_line + 1) != '_'
				&& *(input_line + 1) != RED_IN && *(input_line + 1) != RED_OUT
				&& *(input_line + 1) != PIPE)
				input_line += 2;
			if (*(input_line + 1) == D_QOUTE && *(input_line + 1) == QOUTE)
				input_line += 3;
			if (len == 0)
				continue ;
			enu.type = WORD;
			enu.state = DOLLAR_SIGN;
			add_back(token, ft_new(input_line, len, enu, ptr));
			input_line += len;
		}
		else
		{
			len = ft_get_length(input_line);
			enu.type = WORD;
			add_back(token, ft_new(input_line, len, enu, ptr));
			input_line += len;
		}
	}
}
