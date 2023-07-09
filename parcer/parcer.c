/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:45:23 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/08 18:38:48 by ylachhab         ###   ########.fr       */
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
	return (node);
}

void	ft_expand_in_heredoc(char **input, t_expand	*expand)
{
	if ((*input)[0] == '$' && ((*input)[1] != '\0' && (*input)[1] != '?'))
		ft_expand_here_doc(input, expand);
}

void	ft_parcer(t_token *token, t_cmd **cmd, t_free **ptr, t_expand *expand)
{
	t_cmd	*new;
	t_token	*tmp;
	int		i;
	int		countp;

	tmp = token;
	countp = ft_count_pipe(tmp) + 1;
	while (tmp)
	{
		if (countp > 0 && tmp->type != PIPE)
		{
			i = 0;
			new = ft_new_cmd(ptr, ft_get_cmd(tmp, ptr));
			ft_add_cmd(cmd, new);
			new->arg = ft_get_arg(tmp, ptr);
			ft_open_files(&tmp, &new, expand, &countp);
			countp--;
			if (countp == 0)
				break ;
		}
		tmp = tmp->next;
	}
}
