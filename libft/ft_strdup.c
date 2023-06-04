/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 08:40:00 by nel-baz           #+#    #+#             */
/*   Updated: 2022/10/24 10:34:11 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) + 1;
	str = (char *)malloc(i * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (str && s1[j] != '\0')
	{
		str[j] = s1[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
