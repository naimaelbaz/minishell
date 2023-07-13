/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:26:44 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/12 16:47:23 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split_path(t_expand *expand)
{
	char	*path;
	char	**split;

	path = ft_search_val("PATH", expand);
	split = ft_split(path, ':');
	return (split);
}

int	ft_check_path(char *join)
{
	return (access(join, X_OK) == 0);
}

char	*ft_found_path(char **split, char *cmd, t_free **ptr)
{
	char	*join;
	int		i;

	i = 0;
	if (!split)
		return (NULL);
	while (split[i])
	{
		join = ft_join(split[i], "/");
		join = ft_strjoin(join, cmd);
		ft_add_to_free(ptr, ft_new_node(join));
		if (ft_check_path(join))
			return (join);
		i++;
	}
	return (NULL);
}
