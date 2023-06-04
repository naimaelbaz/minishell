/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:24:23 by nel-baz           #+#    #+#             */
/*   Updated: 2023/06/04 15:57:21 by ylachhab         ###   ########.fr       */
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

int	ft_qoute(t_enum *enu, char **input_line, t_free **ptr,
			t_token **token)
{
	int	len;

	if (**input_line == QOUTE || **input_line == D_QOUTE)
	{
		len = ft_get_length(*input_line);
		if (len == 0)
		{
			*input_line += 2;
			return (1);
		}
		if (**input_line == QOUTE)
			enu->state = IN_QOUTE;
		else if (**input_line == D_QOUTE)
			enu->state = IN_D_QOUTE;
		enu->type = WORD;
		(*input_line)++;
		add_back(token, ft_new(*input_line, len, *enu, ptr));
		(*input_line) += len + 1;
		return (1);
	}
	return (0);
}
