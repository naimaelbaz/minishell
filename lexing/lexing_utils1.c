/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:55:50 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 16:32:55 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_new(char *input_line, int len, t_enum enu, t_free **ptr)
{
	t_token	*node;

	node = ft_malloc(ptr, sizeof(t_token));
	if (!node)
		return (NULL);
	node->data = ft_substr(input_line, 0, len);
	ft_add_to_free(ptr, ft_new_node(node->data));
	node->type = enu.type;
	node->state = enu.state;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_back(t_token **token, t_token *new)
{
	t_token	*ptr;

	ptr = *token;
	if (!token || !new)
		return ;
	if (!ptr)
	{
		*token = new;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	new->prev = ptr;
}

int	ft_check_line(char c)
{
	if ((!c || c == RED_IN || c == RED_OUT || c == WHITE_SPACE
			|| c == PIPE))
		return (1);
	return (0);
}

int	ft_is_special(char c)
{
	if (c == '*' || c == '?' || c == '-' || c == '@'
		|| c == '#' || c == '!')
		return (1);
	return (0);
}
