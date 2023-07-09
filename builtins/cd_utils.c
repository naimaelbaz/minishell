/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:05:26 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/08 11:45:58 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_search_val(char *key, t_expand	*expand)
{
	while (expand)
	{
		if (!ft_strcmp(expand->key, key))
			return (expand->value);
		expand = expand->next;
	}
	return (NULL);
}

void	ft_set_val(char *key, char *value, t_expand **expand)
{
	t_expand	*tmp;

	tmp = *expand;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			tmp->value = value;
			break ;
		}
		tmp = tmp->next;
	}
}
