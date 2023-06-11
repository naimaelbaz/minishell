/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:07:54 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/10 17:47:02 by ylachhab         ###   ########.fr       */
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

void	ft_join_string(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->next && head->data[0] != WHITE_SPACE
			&& head->next->data[0] != WHITE_SPACE
			&& head->next->data[0] != PIPE && head->next->data[0] != RED_IN
			&& head->next->data[0] != RED_OUT
			&& head->data[0] != WHITE_SPACE
			&& head->data[0] != PIPE && head->data[0] != RED_IN
			&& head->data[0] != RED_OUT)
		{
			head->data = ft_join(head->data, head->next->data);
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
		head = head->next;
	}
}
