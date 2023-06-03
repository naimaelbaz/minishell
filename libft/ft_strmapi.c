/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:30:17 by ylachhab          #+#    #+#             */
/*   Updated: 2022/11/08 22:28:28 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	slen;

	i = 0;
	j = 0;
	if (!s || !f)
		return (NULL);
	slen = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (slen + 1));
	if (!str)
		return (NULL);
	while (i < slen)
	{
		str[j] = f(i, s[i]);
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
