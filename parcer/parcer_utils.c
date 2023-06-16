/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:39:41 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/15 19:39:59 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_new_cmd(t_free **ptr, void *content)
{
	t_cmd	*node;

	node = ft_malloc(ptr, sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = content;
	node->input = 0;
	node->output = 1;
	node->next = NULL;
	return (node);
}

void	ft_add_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	ptr = *lst;
	if (!ptr)
	{
		*lst = new;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

int	ft_count_pipe(t_token	*token)
{
	int	p;

	p = 0;
	while (token)
	{
		if (token->type == PIPE)
			p++;
		token = token->next;
	}
	return (p);
}

char	*ft_get_cmd(t_token	*token)
{
	while (token && token->type != PIPE)
	{
		if (token->data[0] == '>' || token->data[0] == '<')
		{
			token = token->next;
			if (token->type == WHITE_SPACE)
				token = token->next;
			if (token->next)
				token = token->next;
			else
				break ;
			continue ;
		}
		if (token->type == WORD && token->data[0] != '\0')
			return (token->data);
		token = token->next;
	}
	return ("(null)");
}

int	ft_len(t_token *token)
{
	int	len;

	len = 0;
	while (token && token->type != PIPE)
	{
		if (token->data[0] == '>' || token->data[0] == '<')
		{
			token = token->next;
			if (token->type == WHITE_SPACE)
				token = token->next;
			if (token->next)
				token = token->next;
			else
				break ;
			continue ;
		}
		if (token->type == WORD)
			len++;
		token = token->next;
	}
	return (len);
}
