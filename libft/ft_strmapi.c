/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 08:14:08 by nel-baz           #+#    #+#             */
/*   Updated: 2022/11/02 19:52:14 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	ln;
	char			*ptr;

	i = 0;
	if (!s || !f)
		return (NULL);
	ln = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * ln + 1);
	if (!ptr)
		return (NULL);
	while (i < ln)
	{
		ptr[i] = (*f)(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
