/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:21:25 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 10:16:53 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_delete_empty_str(t_token **token)
{
	t_token	*tmp ;

	tmp = *token;
	while (tmp)
	{
		if (tmp->data[0] == '\0' && tmp->state == DOLLAR_SIGN)
			tmp->data = NULL;
		tmp = tmp->next;
	}
}

void	ft_exit_expand(char **head, t_free **ptr)
{
	*head = ft_itoa(g_global.exit_global);
	ft_add_to_free(ptr, ft_new_node(*head));
}

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
			new->prev = NULL;
			break ;
		}
		i++;
	}
	return (new);
}

void	ft_exp_add_back(t_expand **lst, t_expand *new)
{
	t_expand	*ptr;

	ptr = *lst;
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
}

t_expand	*ft_get_env(t_main *main, char **env)
{
	t_expand	*expand;
	int			i;
	char		*str;

	i = 0;
	expand = NULL;
	while (env[i])
	{
		ft_exp_add_back(&expand, ft_exp_new(env[i], &main->new_ptr));
		i++;
	}
	ft_exist_variables(main);
	getcwd(g_global.pwd, sizeof(g_global.pwd));
	str = ft_search_val("PWD", expand);
	ft_add_to_free(&main->new_ptr, ft_new_node(str));
	if (str && ft_strcmp(str, g_global.pwd))
		ft_set_val("PWD", g_global.pwd, &expand);
	return (expand);
}
