/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:55:01 by nel-baz           #+#    #+#             */
/*   Updated: 2022/11/02 19:11:31 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	i;

	i = 0;
	s1 = (char *) dst;
	s2 = (char *) src;
	if (dst > src)
	{
		while (len > 0)
		{
			s1[len - 1] = s2[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
