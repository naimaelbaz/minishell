/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:42:49 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/13 09:35:04 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_sort_env(t_expand *expand)
{
	t_expand	*tmp;
	t_expand	*tmp2;
	char		*swap_val;
	char		*swap_key;

	tmp = expand;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->key, tmp2->key) > 0)
			{
				swap_key = tmp->key;
				swap_val = tmp->value;
				tmp->key = tmp2->key;
				tmp->value = tmp2->value;
				tmp2->key = swap_key;
				tmp2->value = swap_val;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (expand);
}

t_expand	*ft_tmp_new(char *key, char *value, t_free **ptr)
{
	t_expand	*new;
	int			i;
	int			nb;

	i = 0;
	nb = 0;
	new = ft_malloc(ptr, sizeof(t_expand));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_expand	*ft_copy_env(t_expand *expand, t_free **ptr)
{
	t_expand	*tmp;

	tmp = NULL;
	while (expand)
	{
		ft_exp_add_back(&tmp, ft_tmp_new(expand->key, expand->value, ptr));
		expand = expand->next;
	}
	return (tmp);
}

void	ft_export(t_expand *expand, int i, t_free **ptr)
{
	char		*str;
	t_expand	*tmp;

	tmp = ft_copy_env(expand, ptr);
	tmp = ft_sort_env(tmp);
	while (tmp)
	{
		if (g_global.path && !ft_strcmp(tmp->key, "PATH"))
		{
			tmp = tmp->next;
			continue ;
		}
		str = ft_join("declare -x ", tmp->key);
		if (tmp->value)
		{
			str = ft_strjoin(str, "=");
			str = ft_strjoin(str, "\"");
			str = ft_strjoin(str, tmp->value);
			str = ft_strjoin(str, "\"");
		}
		ft_putendl_fd(str, i);
		free (str);
		tmp = tmp->next;
	}
	g_global.exit_global = 0;
}
