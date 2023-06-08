/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:49:58 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/08 20:53:07 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


char	*ft_get_value(char *sub, t_expand *expand, int a)
{
	char	*str;
	int		c;

	c = 0;
	while (expand)
	{
		if (!ft_strcmp(sub + 1 , expand->key))
		{
			str = malloc(sizeof(char) * ft_strlen(expand->value));
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

int	ft_check_arg(char c)
{
	if (!c || c == RED_IN || c == RED_OUT || c == PIPE
		|| c == QOUTE || c == WHITE_SPACE)
		return (1);
	return (0);
}

char	*ft_split_expand(char *s, t_expand *expand)
{
	int		i;
	int		start;
	char	*sub;
	char	*join;

	i = 0;
	join = NULL;
	s = ft_strtrim(s, "\"");
	printf("%s\n",s);
	while (s[i])
	{
		if (s[i] && s[i] != ENV_VAR)
		{
			start = i;
			while (s[i] && s[i] != ENV_VAR)
				i++;
			sub = ft_substr(s, start, i - start);
			join = ft_strjoin(join, sub);
			free (sub);
		}
		if (s[i] == ENV_VAR)
		{
			// if (ft_check_arg(s[i + 1]))
			// {
			// 	start = i++;
			// 	while (s[i] && s[i] != WHITE_SPACE && s[i] != PIPE
			// 		&& s[i] != RED_IN && s[i] != RED_OUT
			// 		&& s[i] != D_QOUTE && s[i] != QOUTE && s[i] != ENV_VAR)
			// 		i++;
			// 	sub = ft_substr(s, start, i - start);
			// 	join = ft_strjoin(join, sub);
			// 	free (sub);
			// 	continue;
			// }
			else if (!ft_check_env_var(s[i + 1]))
			{
				i = i + 2;
				continue;
			}
			start = i++;
			while (s[i] && s[i] != WHITE_SPACE && s[i] != PIPE
				&& s[i] != RED_IN && s[i] != RED_OUT
				&& s[i] != D_QOUTE && s[i] != QOUTE && s[i] != ENV_VAR)
				i++;
			sub = ft_substr(s, start, i - start);
			sub = ft_get_value(sub, expand, 1);
			join = ft_strjoin(join, sub);
			free (sub);
		}
	}
	if (!join)
		join = ft_strdup("");
	return (join);
}
