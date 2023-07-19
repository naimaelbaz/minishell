/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 09:32:07 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 08:07:17 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_cd_whithout_arg(t_expand *expand)
{
	char	*home;
	char	*pwd;

	g_global.exit_global = 0;
	home = ft_search_val("HOME", expand);
	pwd = ft_search_val("PWD", expand);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_global.exit_global = 1;
	}
	else if (chdir(home) == 0)
	{
		if (pwd)
			ft_set_val("OLDPWD", pwd, &expand);
		ft_set_val("PWD", home, &expand);
	}
	else
		ft_printf_error(home);
	return (expand);
}

void	ft_printf_error(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	g_global.exit_global = 1;
}

t_expand	*ft_cd_whith_arg(char **arg, t_expand *expand, t_free **new_ptr)
{
	char	*pwd;
	char	*str;

	g_global.exit_global = 0;
	pwd = ft_search_val("PWD", expand);
	if (chdir(arg[1]) == 0)
	{
		if (getcwd(g_global.pwd, sizeof(g_global.pwd)) == NULL)
		{
			ft_putstr_fd("cd: error retrieving current directory:"
				"getcwd: cannot access parent directories: No such"
				"file or directory\n", 2);
			return (expand);
		}
		str = ft_strdup(g_global.pwd);
		ft_add_to_free(new_ptr, ft_new_node(str));
		ft_set_val("OLDPWD", pwd, &expand);
		ft_set_val("PWD", str, &expand);
	}
	else
		ft_printf_error(arg[1]);
	return (expand);
}

t_expand	*ft_cd(t_expand *expand, char **arg, t_free **new_ptr)
{
	if (!arg[1])
		return (ft_cd_whithout_arg(expand));
	return (ft_cd_whith_arg(arg, expand, new_ptr));
}
