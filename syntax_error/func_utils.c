/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:15:15 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 11:04:40 by ylachhab         ###   ########.fr       */
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

int	ft_pipe_first(char *input)
{
	if (input[0] == '|')
		return (1);
	return (0);
}

int	ft_check_pipe(char *input)
{
	int	i;

	i = 0;
	if (ft_pipe_first(input))
		return (1);
	while ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
		i++;
	if (input[i] == '|')
		return (1);
	while (input[i])
	{
		i = ft_check_in_quote(input, i);
		if (input[i++] == '|')
		{
			while (input[i] && ((input[i] >= 9 && input[i] <= 13)
					|| input[i] == 32))
				i++;
			if (input[i] == '|')
				return (1);
			if (input[i] == '\0')
				return (1);
		}
	}
	return (0);
}

int	ft_check_redirect_input(char *input)
{
	int	i;

	i = 0;
	while (input && input[i] != '\0')
	{
		i = ft_check_in_quote(input, i);
		if (input && input[i] == '<')
		{
			i++;
			if (input && input[i] == '<')
				i++;
			i = ft_check_in_quote(input, i);
			while (input[i] && ((input[i] >= 9 && input[i] <= 32)))
				i++;
			if (input[i] == '\0')
				return (1);
			if (input[i] == '>' || input[i] == '|' || input[i] == '<')
				return (1);
		}
		if (input[i])
			i++;
	}
	return (0);
}

int	ft_check_syntax_error(char *input)
{
	if (ft_check_quote_close(input))
		return (ft_putstr_fd("minishell : syntax error\n", 2), 0);
	else if (ft_check_redirect_output(input))
		return (ft_putstr_fd("minishell : syntax syntax error near"
				" unexpected token redirection output\n", 2), 0);
	else if (ft_check_pipe(input))
		return (ft_putstr_fd("minishell : syntax error near "
				"unexpected token `|'\n", 2), 0);
	else if (ft_check_redirect_input(input))
		return (ft_putstr_fd("minishell : syntax syntax error near"
				" unexpected token redirection input\n", 2), 0);
	else if (ft_check_parenthesis(input))
		return (ft_putstr_fd("minishell: syntax error near"
				" unexpected token `)' or `('\n", 2), 0);
	else if (ft_check_brackets(input))
		return (ft_putstr_fd("minishell: syntax error near"
				" unexpected token `{' or `}'\n", 2), 0);
	return (1);
}
