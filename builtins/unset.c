/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:02:42 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/11 15:00:01 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_syntax_unset(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_delete_node(t_expand **tmp, t_expand **expand)
{
	if ((*tmp)->prev == NULL)
	{
		*expand = (*expand)->next;
		(*expand)->prev = NULL;
		(*tmp) = *expand;
		return (1);
	}
	return (0);
}

void	check_exist_var(char *arg, t_expand **expand)
{
	t_expand	*tmp;

	tmp = *expand;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, arg))
		{
			if (tmp->prev == NULL && !tmp->next)
			{
				*expand = NULL;
				break ;
			}
			if (ft_delete_node(&tmp, expand))
				continue ;
			if (!tmp->next)
			{
				tmp->prev->next = NULL;
				break ;
			}
			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
		}
		tmp = tmp->next;
	}
}

t_expand	*ft_unset(char	**arg, t_expand *expand)
{
	int		i;

	i = 1;
	g_global.exit_global = 0;
	while (arg[i])
	{
		if ((!ft_isalpha(arg[i][0]) && arg[i][0] != '_')
			|| !ft_check_syntax_unset(arg[i]))
		{
			ft_print_error(arg[i]);
			i++;
			continue ;
		}
		check_exist_var(arg[i], &expand);
		i++;
	}
	return (expand);
}
