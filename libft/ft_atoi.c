/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:44:10 by nel-baz           #+#    #+#             */
/*   Updated: 2022/11/02 18:58:28 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				signe;
	unsigned long	res;

	res = 0;
	signe = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe *= (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - 48);
		if (res >= 9223372036854775807)
		{
			if (signe == 1)
				return (-1);
			else
				return (0);
		}
	}
	return (res * signe);
}
