/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:07:54 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 08:25:02 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	while (s1[i] && i < (ft_strlen(s1)))
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] && i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_join_check(t_token	*head)
{
	if (head->next && (head->type == IN_D_QOUTE
			|| head->type == IN_QOUTE || head->type == WORD)
		&& (head->next->type == IN_D_QOUTE || head->next->type == IN_QOUTE
			|| head->next->type == WORD))
		return (1);
	return (0);
}

void	ft_join_string(t_token **token, t_free **ptr)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (ft_join_check(head))
		{
			head->data = ft_join(head->data, head->next->data);
			if (head->next->state == IN_D_QOUTE)
				head->state = IN_D_QOUTE;
			if (head->next->state == IN_QOUTE)
				head->state = IN_QOUTE;
			ft_add_to_free(ptr, ft_new_node(head->data));
			head->next = head->next->next;
			continue ;
		}
		head = head->next;
	}
}

void	ft_delete(t_token **token, t_free **ptr)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->next == NULL && head->prev && head->type == WHITE_SPACE
			&& head->data[1] == '\0')
		{
			head->prev->next = NULL;
			break ;
		}
		if (head->state == IN_QOUTE)
		{
			head->data = ft_strtrim(head->data, "\'");
			ft_add_to_free(ptr, ft_new_node(head->data));
		}
		if (head->state == IN_D_QOUTE)
		{
			head->data = ft_strtrim(head->data, "\"");
			ft_add_to_free(ptr, ft_new_node(head->data));
		}
		head = head->next;
	}
}

void	ft_unlink_heredoc(void)
{
	if (g_global.name_hedoc)
	{
		unlink(g_global.name_hedoc);
		close(g_global.hedoc);
		free (g_global.name_hedoc);
		g_global.name_hedoc = NULL;
	}
}
