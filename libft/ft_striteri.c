/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 10:15:47 by nel-baz           #+#    #+#             */
/*   Updated: 2022/11/02 21:35:18 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	ln;

	i = 0;
	if (s && f)
	{
		ln = ft_strlen(s);
		while (i < ln)
		{
			f(i, s + i);
			i++;
		}
	}
}
