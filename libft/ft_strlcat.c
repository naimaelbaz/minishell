/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:31:21 by nel-baz           #+#    #+#             */
/*   Updated: 2022/11/02 15:40:46 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	l;

	j = 0;
	if (!dst && dstsize == 0)
		return (0);
	l = ft_strlen(src) + ft_strlen(dst);
	i = ft_strlen(dst);
	if (dstsize == 0 || dstsize < i)
		return (ft_strlen(src) + dstsize);
	while (src[j] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (l);
}
