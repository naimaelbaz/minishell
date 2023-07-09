/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:21:08 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/08 10:26:30 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_empty_env(t_free **ptr)
{
	t_expand	*expand;
	char		*str;
	char		cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	expand = NULL;
	str = ft_join("PWD=", cwd);
	ft_exp_add_back(&expand, ft_exp_new(str, ptr));
	ft_exp_add_back(&expand, ft_exp_new("SHLVL=1", ptr));
	return (expand);
}

void	ft_pwd(int i)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	if (i != 1)
	{
		ft_putstr_fd(cwd, i);
		ft_putstr_fd("\n", i);
	}
	else
		printf("%s\n", cwd);
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
			if (arg[nb + 1])
				printf("%s", " ");
		}
		nb++;
	}
	if (n == 1 && i == 1)
		printf("\n");
	else if (n == 1 && i != 1)
		ft_putstr_fd("\n", i);
}
