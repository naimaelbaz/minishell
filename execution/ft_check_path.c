/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:28:56 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/09 18:37:29 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split_path(t_expand *expand, t_free **ptr)
{
	char	*path;
	char	**split;

	path = ft_search_val("PATH", expand);
	if (!path)
	{
		path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		ft_add_to_free(ptr, ft_new_node(path));
	}
	split = ft_split(path, ':');
	int i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	return (split);
}