/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:01:01 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/08 21:57:14 by ylachhab         ###   ########.fr       */
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

int	ft_is_spec(char c)
{
	if (c == '*' || c == '-' || c == '@'
		|| c == '#' || c == '!')
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
			if (ft_is_spec(s[i + 1]) || ft_isdigit(s[i + 1]))
			{
				i += 2;
				continue ;
			}
			else if (!ft_isalpha(s[i + 1]))
			{
				start = i++;
				while (s[i] && s[i] != WHITE_SPACE && s[i] != PIPE
					&& s[i] != RED_IN && s[i] != RED_OUT
					&& s[i] != D_QOUTE && s[i] != QOUTE && s[i] != ENV_VAR && !ft_is_special(s[i]))
					i++;
				sub = ft_substr(s, start, i - start);
				join = ft_strjoin(join, sub);
				free (sub);
				continue;
			}
			start = i++;
			while (s[i] && s[i] != WHITE_SPACE && s[i] != PIPE
				&& s[i] != RED_IN && s[i] != RED_OUT
				&& s[i] != D_QOUTE && s[i] != QOUTE && s[i] != ENV_VAR && !ft_is_special(s[i]))
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

void	ft_expanding(t_token **token, t_expand *expand, t_free **ptr)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->state == IN_D_QOUTE)
		{
			head->data = ft_split_expand(head->data, expand);
			ft_add_to_free(ptr, ft_new_node(head->data));
		}
		else if (head->state == DOLLAR_SIGN && head->data[0] == ENV_VAR
			&& (head->data[1] != '\0' &&  head->data[1] != '?'))
		{
			if (ft_isdigit(head->data[1]))
			{
				head->data += 2;
				head->data = ft_substr(head->data, 0, ft_strlen(head->data));
				ft_add_to_free(ptr, ft_new_node(head->data));
			}
			else
			{
				head->data = ft_get_value(head->data, expand, 0);
				ft_add_to_free(ptr, ft_new_node(head->data));
			}
		}
		head = head->next;
	}
}