/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:45:23 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/23 18:40:16 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			new = ft_new_cmd(ptr, ft_get_cmd(tmp));
			ft_add_cmd(cmd, new);
			new->arg = ft_get_arg(tmp, ptr);
			ft_open_files(&tmp, &new, expand);
			countp--;
			if (countp == 0)
				break ;
		}
		tmp = tmp->next;
	}
}
