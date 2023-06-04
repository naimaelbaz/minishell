/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:34:03 by nel-baz           #+#    #+#             */
/*   Updated: 2022/11/02 17:20:12 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	nb;
	void	*ptr;

	nb = count * size;
	ptr = malloc(nb);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nb);
	return (ptr);
}
