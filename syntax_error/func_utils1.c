/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:17:29 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/07 17:52:37 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_in_quote(char *input, int i)
{
	if (input[i] == '\"')
	{
		i++;
		while (input[i] && input[i] != '\"')
			i++;
	}
	if (input[i] == '\'')
	{
		i++;
		while (input[i] && input[i] != '\'')
			i++;
	}
	return (i);
}

int	ft_check_redirect_output(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		i = ft_check_in_quote(input, i);
		if (input[i] == '>')
		{
			i++;
			if (input[i] == '>')
				i++;
			while (input[i] && ((input[i] >= 9 && input[i] <= 13)
					|| input[i] == 32))
				i++;
			if (input[i] == '\0')
				return (1);
			if (input[i] == '>' || input[i] == '|' || input[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}
