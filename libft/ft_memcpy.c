/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:14:02 by nel-baz           #+#    #+#             */
/*   Updated: 2022/11/02 22:25:26 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*tmp;
	char	*tmp1;

	tmp = (char *) dest;
	tmp1 = (char *) src;
	if (tmp == NULL && tmp1 == NULL)
		return (NULL);
	while (n > 0)
	{
		*tmp++ = *tmp1++;
		n--;
	}
	return (dest);
}
