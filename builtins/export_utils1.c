/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 09:13:16 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 19:13:58 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_key(char *arg, t_export *export)
{
	if (arg[export->j - 1] == '+')
	{
		export->plus = 1;
		export->key = ft_substr(arg, 0, export->j - 1);
		if (!ft_check_syntax(export->key))
		{
			free (export->key);
			ft_print_error(arg);
			export->nb = 1;
			return ;
		}
	}
	else
	{
		export->key = ft_substr(arg, 0, export->j);
		if (!ft_check_syntax(export->key))
		{
			free (export->key);
			ft_print_error(arg);
			export->nb = 1;
			return ;
		}
	}
}

void	ft_get_key2(char *arg, t_export *export, t_free **ptr)
{
	while (arg[export->j])
	{
		if (arg[export->j] == '=')
		{
			ft_get_key(arg, export);
			if (!export->key)
				break ;
			ft_add_to_free(ptr, ft_new_node(export->key));
			export->val = ft_substr(arg, export->j + 1, ft_strlen(arg));
			ft_add_to_free(ptr, ft_new_node(export->val));
			export->nb = 1;
			break ;
		}
		export->j++;
	}
}

void	ft_init(t_export *export)
{
	export->plus = 0;
	export->nb = 0;
	export->j = 0;
}

void	ft_error_syntax(t_export *export, char *arg)
{
	ft_print_error(arg);
	export->i++;
	export->nb = 1;
}

t_expand	*ft_add_export(t_expand *expand, char **arg, t_free **ptr)
{
	t_export	export;

	export.i = 1;
	while (arg[export.i])
	{
		ft_init(&export);
		if (!ft_isalpha(arg[export.i][0]) && arg[export.i][0] != '_')
		{
			ft_error_syntax(&export, arg[export.i]);
			continue ;
		}
		ft_get_key2(arg[export.i], &export, ptr);
		if (ft_check(arg[export.i], &export, ptr))
		{
			export.i++;
			continue ;
		}
		if (!ft_check_arg(export.key, export.val, &expand, export.plus)
			&& ft_check_syntax(export.key))
			ft_exp_add_back(&expand,
				ft_export_new(export.key, export.val, ptr));
		export.i++;
	}
	return ((!export.nb && (g_global.exit_global = 0)), expand);
}
