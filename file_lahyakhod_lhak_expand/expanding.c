/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:37:01 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/07 19:42:48 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_exp_new(char *env, t_free **ptr)
{
	t_expand	*new;
	int			i;

	i = 0;
	new = ft_malloc(ptr, sizeof(t_expand));
	if (!new)
		return (NULL);
	while (env[i])
	{
		if (env[i] == '=')
		{
			new->key = ft_substr(env, 0, i);
			ft_add_to_free(ptr, ft_new_node(new->key));
			new->value = ft_substr(env, i + 1, ft_strlen(env));
			ft_add_to_free(ptr, ft_new_node(new->value));
			new->next = NULL;
			break ;
		}
		i++;
	}
	return (new);
}

void	ft_exp_add_back(t_expand **lst, t_expand *new)
{
	t_expand	*ptr;

	if (!lst || !new)
		return ;
	ptr = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (ptr && ptr->next != NULL)
			ptr = ptr -> next;
		ptr -> next = new;
	}
}

void	*ft_avoid_leak(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
	return (NULL);
}

t_expand	*ft_get_env(t_free **ptr, char **env)
{
	t_expand	*expand;
	int			i;

	i = 0;
	expand = NULL;
	while (env[i])
	{
		ft_exp_add_back(&expand, ft_exp_new(env[i], ptr));
		i++;
	}
	return (expand);
}


int	ft_check_env_var(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

// int	my_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && (!(str[i] >= 9 && str[i] <= 13) || str[i] != 32) && str[i] != '$')
// 		i++;
// 	return (i);
// }

void	ft_expanding(t_token **token, t_expand *expand, t_free **ptr)
{
	t_token	*head;

	head = *token;
	(void)ptr;
	while (head)
	{
		if (head->state == IN_D_QOUTE)
		{
			head->data = ft_split_expand(head->data, expand);
			ft_add_to_free(ptr, ft_new_node(head->data));
		}
		// else if (head->state == DOLLAR_SIGN && head->data[1] != '\0')
		// {
		// 	head->data = ft_get_value(head->data, expand, 0);
		// 	ft_add_to_free(ptr, ft_new_node(head->data));
		// }
		head = head->next;
	}
}
