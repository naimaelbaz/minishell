/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 10:01:01 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 19:07:03 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_condition(char **join, int flag, char *s)
{
	!(*join) && (*join = ft_strdup(""));
	if (!flag)
		free (s);
}

int	ft_special_variable(char c)
{
	if (c == '*' || c == '-' || c == '@'
		|| c == '#' || c == '!')
		return (1);
	return (0);
}

void	ft_skip_special(char *s, int *i)
{
	while (!ft_special_variable(s[*i])
		&& (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
}

void	ft_get_next(t_token **head)
{
	(*head) = (*head)->next;
	while ((*head) && (*head)->type != WHITE_SPACE)
		(*head) = (*head)->next;
}

void	ft_expanding(t_token **token, t_expand *expand, t_free **ptr, int flag)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->prev && (head->prev->type == HERE_DOC
				|| (head->prev->prev && head->prev->prev->type == HERE_DOC)))
		{
			ft_get_next(&head);
			continue ;
		}
		else if (head->state == IN_D_QOUTE
			|| (head->state == IN_QOUTE && flag == 1))
		{
			head->data = ft_split_expand(head->data, expand, flag);
			ft_add_to_free(ptr, ft_new_node(head->data));
		}
		else if (head->state == DOLLAR_SIGN && head->data[0] == ENV_VAR
			&& (head->data[1] != '\0' && head->data[1] != '?'))
			ft_dollarsign_inword(&head->data, expand, ptr);
		else if (!ft_strcmp(head->data, "$?"))
			ft_exit_expand(&head->data, ptr);
		head = head->next;
	}
}
