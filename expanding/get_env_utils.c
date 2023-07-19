/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:28:42 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 09:52:46 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_expandsize(t_expand *lst)
{
	t_expand	*ptr;
	int			count;

	count = 0;
	if (!lst)
		return (0);
	ptr = NULL;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

char	**myenv(t_expand *expand, t_free **ptr)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_malloc(ptr, sizeof(char *) * (ft_expandsize(expand) + 1));
	while (expand)
	{
		tmp[i] = ft_join(expand->key, "=");
		tmp[i] = ft_strjoin(tmp[i], expand->value);
		expand = expand->next;
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	ft_exist_variables(t_main *main)
{
	char	*str;
	char	*join;

	if (!ft_search_val("PWD", main->expand))
	{
		join = ft_join("PWD=", getcwd(g_global.pwd, sizeof(g_global.pwd)));
		ft_add_to_free(&main->new_ptr, ft_new_node(join));
		ft_exp_add_back(&main->expand, ft_exp_new(join, &main->new_ptr));
	}
	if (!ft_search_val("_", main->expand))
		ft_exp_add_back(&main->expand,
			ft_exp_new("_=/usr/bin/env", &main->new_ptr));
	if (!ft_search_val("PATH", main->expand))
	{
		str = ft_join("PATH=", _PATH_STDPATH);
		ft_add_to_free(&main->new_ptr, ft_new_node(str));
		ft_exp_add_back(&main->expand, ft_exp_new(str, &main->new_ptr));
	}
}

void	ft_put_env(t_main *main, char **env)
{
	getcwd(g_global.pwd, sizeof(g_global.pwd));
	ft_init_var(main, 0);
	if (env[0] == NULL)
	{
		g_global.path = 1;
		main->expand = ft_empty_env(main);
	}
	else
		main->expand = ft_get_env(main, env);
	ft_exist_variables(main);
	g_global.shlvl = ft_atoi(ft_search_val("SHLVL", main->expand));
	if (g_global.shlvl == 999)
	{
		ft_set_val("SHLVL", "", &main->expand);
		return ;
	}
	if (g_global.shlvl < 0)
		g_global.shlvl = -1;
	if (g_global.shlvl >= 1000)
		g_global.shlvl = 0;
	ft_set_val("SHLVL", ft_itoa(g_global.shlvl + 1), &main->expand);
}
