/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:01:01 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/23 18:03:53 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_env(char *s, int *i, int start, char **join)
{
	char	*sub;

	if (ft_is_spec(s[*i + 1]) || ft_isdigit(s[*i + 1]))
		return (*i += 2, 1);
	else if (!ft_isalpha(s[*i + 1]))
	{
		start = (*i)++;
		while (s[*i] && ft_is_enum(s[*i]) && !ft_is_special(s[*i]))
			(*i)++;
		sub = ft_substr(s, start, *i - start);
		*join = ft_strjoin(*join, sub);
		return (free (sub), 1);
	}
	return (0);
}

int	ft_isnot_env(char *s, int *i, int start, char **join)
{
	char	*sub;

	start = *i;
	while (s[*i] && s[*i] != ENV_VAR)
		(*i)++;
	sub = ft_substr(s, start, *i - start);
	*join = ft_strjoin(*join, sub);
	free (sub);
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
		s[i] && s[i] != ENV_VAR && ft_isnot_env(s, &i, start, &join);
		if (s[i] == ENV_VAR)
		{
			if (ft_is_env(s, &i, start, &join))
				continue ;
			start = i++;
			while (!ft_is_special(s[i]) && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
			sub = ft_get_value(ft_substr(s, start, i - start), expand, 1);
			join = ft_strjoin(join, sub);
			free (sub);
		}
	}
	!join && (join = ft_strdup(""));
	return (free (s), join);
}

void	ft_dollarsign_inword(char **str, t_expand *expand, t_free **ptr)
{
	if (ft_isdigit((*str)[1]))
	{
		*str += 2;
		*str = ft_substr(*str, 0, ft_strlen(*str));
		ft_add_to_free(ptr, ft_new_node(*str));
	}
	else
	{
		*str = ft_get_value(*str, expand, 0);
		ft_add_to_free(ptr, ft_new_node(*str));
	}
}

void	ft_expanding(t_token **token, t_expand *expand, t_free **ptr)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->prev && (head->prev->type == HERE_DOC
				|| (head->prev->prev && head->prev->prev->type == HERE_DOC)))
		{
			head = head->next;
			while (head && head->type != WHITE_SPACE)
				head = head->next;
			continue ;
		}
		else if (head->state == IN_D_QOUTE)
		{
			head->data = ft_split_expand(head->data, expand);
			ft_add_to_free(ptr, ft_new_node(head->data));
		}
		else if (head->state == DOLLAR_SIGN && head->data[0] == ENV_VAR
			&& (head->data[1] != '\0' && head->data[1] != '?'))
			ft_dollarsign_inword(&head->data, expand, ptr);
		head = head->next;
	}
}
