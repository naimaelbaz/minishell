/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 09:12:16 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 19:14:54 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_put_error(char *str, int flag)
{
	if (!flag)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_global.exit_global = 255;
	exit (255);
}

void	ft_check_signed(char c, int *i, int *sign)
{
	if (c == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (c == '+')
		(*i)++;
}

int	ft_atoi_util(char *str, int flag)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '\0')
		ft_put_error(str, flag);
	ft_check_signed(str[i], &i, &sign);
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		if ((result > 9223372036854775807ULL && sign == 1)
			|| (result > 9223372036854775808ULL && sign == -1))
			ft_put_error(str, flag);
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		ft_put_error(str, flag);
	return (result * sign);
}

void	ft_exit(char **args, int flag)
{
	int	num;

	g_global.exit_global = 0;
	if (!args[1])
	{
		if (!flag)
			ft_putstr_fd("exit\n", 2);
		exit (0);
	}
	else
	{
		num = ft_atoi_util(args[1], flag);
		if (args[2])
		{
			if (!flag)
				ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_global.exit_global = 1;
			return ;
		}
		if (!flag)
			ft_putstr_fd("exit\n", 2);
		g_global.exit_global = num;
		exit (g_global.exit_global);
	}
}
