/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:28:56 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/09 16:34:16 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	ft_split_path(t_expand *expand, t_free **ptr)
{
	char	*path;
	char	**split;

	path = ft_search_val("PATH", expand);
	if (!path)
	{
		path = ft_strdup("/Users/ylachhab/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/ylachhab/.brew/bin");
		ft_add_to_free(ptr, ft_new_node())
	}
}