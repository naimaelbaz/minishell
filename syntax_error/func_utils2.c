/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:05:11 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/12 18:28:14 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_parenthesis(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		i = ft_check_in_quote(input, i);
		if (input[i] == '(' || input[i] == ')')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_brackets(char *input)
{
	if (!ft_strcmp(input, "{") || !ft_strcmp(input, "}"))
		return (1);
	return (0);
}
