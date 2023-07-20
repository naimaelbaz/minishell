/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 09:39:59 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 09:58:20 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		&& input_line[i] != ENV_VAR && input_line[i] != '\t')
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

void	ft_lexing(char *input_line, t_token	**token, t_free	**ptr)
{
	t_enum	enu;
	int		len;

	while (input_line && (*input_line == WHITE_SPACE || *input_line == '\t'))
			input_line++;
	while (input_line && *input_line)
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
