/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 09:10:32 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 17:32:03 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_export_new(char *key, char *val, t_free **ptr)
{
	t_expand	*new;

	new = ft_malloc(ptr, sizeof(t_expand));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = val;
	new->next = NULL;
	return (new);
}

int	ft_check_arg(char *key, char *val, t_expand **expand, int plus)
{
	t_expand	*tmp;

	tmp = *expand;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (val)
			{
				if (plus == 1)
					tmp->value = ft_strjoin(tmp->value, val);
				else
					tmp->value = val;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_check_syntax(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

void	ft_print_error(char *arg)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
	g_global.exit_global = 1;
}

int	ft_check(char *arg, t_export *export, t_free **ptr)
{
	if (!export->nb)
	{
		export->key = ft_strdup(arg);
		if (!ft_check_syntax(export->key))
		{
			free (export->key);
			ft_print_error(arg);
			export->nb = 1;
			return (1);
		}
		ft_add_to_free(ptr, ft_new_node(export->key));
		export->val = NULL;
	}
	return (0);
}
