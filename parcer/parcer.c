/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:45:23 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 10:39:37 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	new->prev = ptr;
}

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
	node->prev = NULL;
	return (node);
}

void	ft_expand_in_heredoc(char *input, t_main **main,
			t_token **here, t_token *tmp)
{
	g_global.flag = 1;
	ft_lexing(input, here, &(*main)->ptr);
	if (tmp->state != IN_D_QOUTE && tmp->state != IN_QOUTE)
		ft_expanding(here, (*main)->expand, &(*main)->ptr, 1);
}

int	ft_parcer(t_main **main)
{
	t_cmd	*new;
	t_token	*tmp;
	int		i;
	int		countp;

	tmp = (*main)->token;
	countp = ft_count_pipe(tmp) + 1;
	while (tmp)
	{
		if (countp > 0 && tmp->type != PIPE)
		{
			i = 0;
			new = ft_new_cmd(&(*main)->ptr, ft_get_cmd(tmp, &(*main)->ptr));
			ft_add_cmd(&(*main)->cmd, new);
			new->f = 0;
			new->arg = ft_get_arg(tmp, &(*main)->ptr);
			if (ft_open_files(&tmp, &new, main, &countp))
				return (1);
			countp--;
			if (countp == 0)
				break ;
		}
		tmp = tmp->next;
	}
	return (0);
}
