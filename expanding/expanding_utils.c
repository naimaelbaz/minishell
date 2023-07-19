/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:01:39 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 17:10:01 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_enum(char c)
{
	if (c != WHITE_SPACE && c != PIPE && c != RED_IN
		&& c != RED_OUT && c != D_QOUTE && c != QOUTE
		&& c != ENV_VAR)
		return (1);
	return (0);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

int	ft_is_spec(char c)
{
	if (c == '*' || c == '-' || c == '@'
		|| c == '#' || c == '!' || c == ENV_VAR)
		return (1);
	return (0);
}

char	*ft_get_value(char *sub, t_expand *expand, int a)
{
	char	*str;
	int		c;

	c = 0;
	while (expand)
	{
		if (!ft_strcmp(sub + 1, expand->key))
		{
			if (!expand->value)
				break ;
			str = malloc(sizeof(char) * (ft_strlen(expand->value) + 1));
			str = ft_strcpy(str, expand->value);
			c++;
		}
		expand = expand->next;
	}
	if (c == 0)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	if (a == 1)
		free (sub);
	return (str);
}
