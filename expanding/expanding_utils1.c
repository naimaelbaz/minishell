/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:43:10 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 16:54:06 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_env(char *s, int *i, int start, char **join)
{
	char	*sub;

	if (ft_is_spec(s[*i + 1]) || ft_isdigit(s[*i + 1]))
		return (*i += 2, 1);
	else if (!ft_isalpha(s[*i + 1]) && s[*i + 1] != '?')
	{
		start = (*i)++;
		while (s[*i] && ft_is_enum(s[*i]) && !ft_is_special(s[*i]))
			(*i)++;
		sub = ft_substr(s, start, *i - start);
		*join = ft_strjoin(*join, sub);
		return (free (sub), 1);
	}
	return (0);
}

int	ft_isnot_env(char *s, int *i, int start, char **join)
{
	char	*sub;

	start = *i;
	while (s[*i] && s[*i] != ENV_VAR)
		(*i)++;
	sub = ft_substr(s, start, *i - start);
	*join = ft_strjoin(*join, sub);
	free (sub);
	return (0);
}
