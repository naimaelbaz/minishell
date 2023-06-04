/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:56:02 by nel-baz           #+#    #+#             */
/*   Updated: 2022/10/26 19:48:01 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	j;
	size_t	start;
	size_t	end;

	end = 0;
	start = 0;
	if (!s1)
		return (NULL);
	if (set == 0)
		return ((char *)s1);
	j = ft_strlen(s1);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	if (start >= ft_strlen(s1))
		return (ft_strdup(""));
	while (j > 0 && s1 && ft_strchr(set, s1[j]))
	{
		end++;
		j--;
	}
	j = ft_strlen(s1) - start;
	return (ft_substr(s1, start, (j - end) + 1));
}
