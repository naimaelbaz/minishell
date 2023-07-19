/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:03:55 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 19:07:00 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_split_expand(char *s, t_expand *expand, int flag)
{
	int		i;
	int		start;
	char	*sub;
	char	*join;

	i = 0;
	join = NULL;
	(!flag) && (s = ft_strtrim(s, "\""));
	while (s[i])
	{
		s[i] && s[i] != ENV_VAR && ft_isnot_env(s, &i, start, &join);
		if (s[i] == ENV_VAR)
		{
			if (ft_is_env(s, &i, start, &join))
				continue ;
			if (ft_is_dollar_signe(s, &i, &sub, &join))
				continue ;
			start = i++;
			ft_skip_special(s, &i);
			sub = ft_get_value(ft_substr(s, start, i - start), expand, 1);
			join = ft_strjoin(join, sub);
			free (sub);
		}
	}
	return (ft_check_condition(&join, flag, s), join);
}

void	ft_dollarsign_inword(char **str, t_expand *expand, t_free **ptr)
{
	if (ft_isdigit((*str)[1]))
	{
		*str += 2;
		*str = ft_substr(*str, 0, ft_strlen(*str));
		ft_add_to_free(ptr, ft_new_node(*str));
	}
	else
	{
		*str = ft_get_value(*str, expand, 0);
		ft_add_to_free(ptr, ft_new_node(*str));
	}
}

int	ft_is_dollar_signe(char *s, int *i, char **sub, char **join)
{
	if (ft_strchr((s + *i) + 1, '?'))
	{
		*sub = ft_itoa(g_global.exit_global);
		*join = ft_strjoin(*join, *sub);
		(*i) += 2;
		return (1);
	}
	return (0);
}
