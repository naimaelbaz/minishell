/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:51:17 by ylachhab          #+#    #+#             */
/*   Updated: 2022/11/09 04:56:57 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	debut;
	size_t	fin;
	size_t	i;

	i = 0;
	debut = 0;
	if (!s1 || !set)
		return (NULL);
	fin = ft_strlen(s1);
	while (s1[debut] && (ft_strchr(set, (int ) s1[debut]) != NULL))
		debut++;
	while (fin > debut && (ft_strchr(set, (int ) s1[fin - 1]) != NULL))
		fin--;
	str = (char *)malloc(sizeof(char) * (fin - debut + 1));
	if (!str)
		return (0);
	while (debut < fin)
	{
		str[i] = s1[debut];
		i++;
		debut++;
	}
	str[i] = '\0';
	return (str);
}
