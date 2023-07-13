/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:43:12 by nel-baz           #+#    #+#             */
/*   Updated: 2023/07/11 14:45:11 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(t_free **ptr)
{
	t_free	*tmp;

	while (ptr && *ptr)
	{
		tmp = (*ptr)->next;
		free ((*ptr)->ptr);
		free (*ptr);
		*ptr = tmp;
	}
	(*ptr) = NULL;
}

t_free	*ft_new_node(void *content)
{
	t_free	*node;

	node = malloc(sizeof(t_free));
	if (!node)
		return (NULL);
	node->ptr = content;
	node->next = NULL;
	return (node);
}

void	ft_add_to_free(t_free **lst, t_free *new)
{
	t_free	*ptr;

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

void	*ft_malloc(t_free **ptr, int size)
{
	void	*new;

	new = malloc(sizeof(void) * size);
	if (!new)
		return (NULL);
	ft_add_to_free(ptr, ft_new_node(new));
	return (new);
}
