/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 09:12:16 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/09 14:58:11 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_put_error(char *str)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit_global = 255;
	exit (255);
}

int	ft_atoi_util(char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
			sign = -1;
			i++;
	}
	else if (str[i] == '+')
				i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result *= 10;
		result += str[i] - 48;
		if ((result > 9223372036854775807ULL && sign == 1) || (result > 9223372036854775808ULL && sign == -1))
    			ft_put_error(str);
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		ft_put_error(str);
	return (result * sign);
}
// TODO exit_global = num overflow
void	ft_exit(char **args, t_free **ptr)
{
	int	num;

	(void)ptr;
	if (!args[1])
	{
		ft_putstr_fd("exit\n", 2);
		exit_global = 0;
		exit (0);
	}
	else
	{
		num = ft_atoi_util(args[1]);
		if (args[2])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return ;
		}
		ft_putstr_fd("exit\n", 2);
		exit_global = num;
		exit (num);
	}
}