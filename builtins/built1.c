/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:21:08 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 08:09:45 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_empty_env(t_main *main)
{
	t_expand	*expand;
	char		*str;

	expand = NULL;
	getcwd(g_global.pwd, sizeof(g_global.pwd));
	str = ft_join("PWD=", g_global.pwd);
	ft_add_to_free(&main->new_ptr, ft_new_node(str));
	ft_exp_add_back(&expand, ft_exp_new(str, &main->new_ptr));
	ft_exp_add_back(&expand, ft_exp_new("SHLVL=1", &main->new_ptr));
	ft_exp_add_back(&expand, ft_exp_new("_=/usr/bin/env", &main->new_ptr));
	ft_exp_add_back(&expand, ft_exp_new("PATH=/usr/gnu/bin:/usr/local/bin:"
			"/bin:/usr/bin:.", &main->new_ptr));
	ft_exist_variables(main);
	return (expand);
}

void	ft_pwd(int i)
{
	if (!getcwd(g_global.pwd, sizeof(g_global.pwd))
		&& !access(g_global.pwd, F_OK | R_OK | X_OK | W_OK))
	{
		ft_putstr_fd("minishell: pwd", 2);
		return ;
	}
	ft_putendl_fd(g_global.pwd, i);
	g_global.exit_global = 0;
}

int	ft_norme(char *str, int *k, int *j, int *nb)
{
	while (str[*k] == 'n')
		(*k)++;
	if (str[*k] == '\0')
	{
		*nb = *j + 1;
		return (0);
	}
	else
		return (*nb);
}

int	ft_search(char **str)
{
	int	j;
	int	k;
	int	nb;

	j = 0;
	nb = 1;
	while (str[++j])
	{
		k = -1;
		while (str[j][++k])
		{
			if (str[j][k] == '-' && str[j][k + 1] == 'n')
			{
				k++;
				if (!ft_norme(str[j], &k, &j, &nb))
					break ;
				else
					return (nb);
			}
			else
				return (nb);
		}
	}
	return (nb);
}

void	ft_echo(int i, char **arg)
{
	int	nb;
	int	n;

	nb = ft_search(arg);
	n = nb;
	while (arg[nb])
	{
		if (i != 1)
		{
			ft_putstr_fd(arg[nb], i);
			if (arg[nb + 1])
				ft_putstr_fd(" ", i);
		}
		else
		{
			printf("%s", arg[nb]);
			arg[nb + 1] && printf("%s", " ");
		}
		nb++;
	}
	if (n == 1 && i == 1)
		printf("\n");
	else if (n == 1 && i != 1)
		ft_putstr_fd("\n", i);
	g_global.exit_global = 0;
}
