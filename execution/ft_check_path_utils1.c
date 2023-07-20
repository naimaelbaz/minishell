/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:59:49 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 07:50:27 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_is_a_directory(t_cmd *cmd, t_free **ptr, t_expand **expand)
{
	struct stat	state;

	stat(cmd->cmd, &state);
	if (S_ISDIR(state.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		exit (126);
	}
	if (!ft_strcmp(cmd->cmd, "./minishell"))
	{
		g_global.shlvl = ft_atoi(ft_search_val("SHLVL", *expand));
		if (g_global.shlvl == 0 && g_global.delete_shlvl)
			ft_exp_add_back(expand, ft_exp_new("SHLVL=0", ptr));
	}
}

void	ft_exist_file(t_cmd *cmd)
{
	struct stat	state;

	if (access(cmd->cmd, X_OK | R_OK | F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		if (stat(cmd->cmd, &state) == 0)
			exit (126);
		else
			exit (127);
	}
}
