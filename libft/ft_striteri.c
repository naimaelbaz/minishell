/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:06:58 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/04 15:45:00 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s != 0 && f != 0)
	{
		i = 0;
		while (s[i])
		{
			f(i, s + i);
			i++;
		}
	}
}
