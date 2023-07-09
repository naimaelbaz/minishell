/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 09:32:07 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/08 11:45:38 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_cd_whithout_arg(t_expand *expand)
{
	char	*home;
	char	*pwd;

	home = ft_search_val("HOME", expand);
	pwd = ft_search_val("PWD", expand);
	if (!home)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	if (chdir(home) == 0)
	{
		if (pwd)
			ft_set_val("OLDPWD", pwd, &expand);
		ft_set_val("PWD", home, &expand);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(home, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (expand);
}

void	ft_printf_error(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

t_expand	*ft_cd_whith_arg(char **arg, t_expand *expand, t_free **new_ptr)
{
	char	*pwd;
	char	*str;
	char	cwd[PATH_MAX];

	pwd = ft_search_val("PWD", expand);
	if (chdir(arg[1]) == 0)
	{
		getcwd(cwd, sizeof(cwd));
		str = ft_strdup(cwd);
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
