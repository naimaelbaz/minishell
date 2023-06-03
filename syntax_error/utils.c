/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:15:15 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/03 17:40:33 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quote_close(char *input)
{
	int	i;
	int	quote;
	int	dquote;

	i = -1;
	quote = 0;
	dquote = 0;
	while (input[++i] != '\0')
	{
		if (input[i] == '\"')
		{
			if (quote % 2 == 0)
				dquote++;
		}
		else if (input[i] == '\'')
		{
			if (dquote % 2 == 0)
				quote++;
		}
	}
	if (quote % 2 != 0)
		return (1);
	if (dquote % 2 != 0)
		return (1);
	return (0);
}

int	ft_pipe_end(char *input)
{
	int	len;

	len = ft_strlen((const char *)input);
	if (input[0] == '|')
		return (1);
	return (0);
}

int	ft_check_pipe(char *input)
{
	int	i;

	i = 0;
	if (ft_pipe_end(input))
		return (1);
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	if (input[i] == '|')
		return (1);
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i] && ((input[i] >= 9 && input[i] <= 13) || input[i] == 32))
				i++;
			if (input[i] == '|')
				return (1);
			if (input[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_syntax_error(char *input)
{
	if (ft_check_pipe(input))
		printf("minishell : syntax error near unexpected token `|'\n");
	else if (ft_check_quote_close(input))
		printf("minishell : syntax error\n");
	// else
	// 	printf("OK\n");
	return (0);
}
