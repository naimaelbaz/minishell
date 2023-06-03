/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:01:51 by ylachhab          #+#    #+#             */
/*   Updated: 2022/11/07 15:22:08 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;
	int		j;
	char	a;

	j = 0;
	a = (char)c;
	ptr = (char *)str;
	if (a == 0)
		return (ptr + ft_strlen(ptr));
	while (ptr[j])
	{
		if (ptr[j] == a)
			return (ptr + j);
		j++;
	}
	return (NULL);
}
