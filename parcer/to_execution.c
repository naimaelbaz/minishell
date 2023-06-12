/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:39:41 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/12 16:34:42 by ylachhab         ###   ########.fr       */
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

int	ft_count_arg(t_token *token)
{
	int	len;

	len = 0;
	while (token && token->type != PIPE)
	{
		if (token->type != RED_IN)
		{
			token = token->next;
			token = token->next;
		}
		if (token->type != RED_OUT)
		{
			token = token->next;
			token = token->next;
		}
		if (token->type != WHITE_SPACE)
			token = token->next;
		len++;
		token = token->next;
	}
}

void	ft_parcer(t_token *token, t_cmd **cmd, t_free **ptr)
{
	int	pipefd[2];
	t_cmd	*new;
	t_token	*tmp;
	int i;

	tmp = token;
	while (token)
	{
		if (token->type == PIPE)
		{
			pipe(pipefd);
			if (tmp->type == WORD)
			{
				i = 0;
				new = ft_new_cmd(ptr, tmp->data);
				ft_add_cmd(cmd, new);
				new->output = pipefd[1];
				new->arg = malloc(sizeof(char *) * 3);
				new->arg[2] = NULL;
				while (tmp && tmp->type != PIPE)
				{
					if (tmp && tmp->type == RED_IN)
					{
						if (tmp->next->type == WHITE_SPACE)
							tmp = tmp->next;
						new->input = open(tmp->data, O_TRUNC);
						if (new->input == -1)
							printf("%s: No such file or directory\n", tmp->data);
						tmp = tmp->next;
					}
					if (tmp && tmp->type == RED_OUT)
					{
						if (tmp->next->type == WHITE_SPACE)
							tmp = tmp->next;
						new->output = open (tmp->data, O_CREAT | O_TRUNC);
						tmp = tmp->next;
					}
					if (tmp && tmp->type == RED_APP_OUT)
					{
						if (tmp->next->type == WHITE_SPACE)
							tmp = tmp->next;
						new->output = open(tmp->data, O_CREAT);
						tmp = tmp->next;
					}
					if (tmp && tmp->type != WHITE_SPACE && tmp->type != PIPE)
					{
						puts("hi");
						new->arg[i] = tmp->data;
						i++;
					}
					tmp = tmp->next;
				}
			}
		}
		token = token->next;
	}
}
