/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:21:25 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/08 17:21:27 by ylachhab         ###   ########.fr       */
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
