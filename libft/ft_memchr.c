/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:09:05 by ylachhab          #+#    #+#             */
/*   Updated: 2022/11/09 04:24:05 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*b;
	size_t			i;

	i = 0;
	b = (unsigned char *)str;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (b[i] == (unsigned char)c)
			return (b + i);
		i++;
	}
	return (NULL);
}
