/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:28:56 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/16 17:25:15 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_is_absolute_path(char *cmd)
{
	return (ft_strchr(cmd, '/'));
}

void	ft_cmd_not_found(char *cmd)
{
	// if (a)
	ft_putstr_fd("minshell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit (127);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free (split[i]);
		i++;
	}
	free (split);
	split = NULL;
}

void	ft_dup_file(t_cmd *cmd, t_cmd *h)
{
	if (cmd->output != 1)
		dup2(cmd->output, 1);
	if (cmd->input != 0 && g_global.input == 0)
		dup2(cmd->input, 0);
	while (h)
	{
		if (h->output != 1)
			close(h->output);
		if (h->input != 0)
			close(h->input);
		h = h->next;
	}
}

void	to_be_executed(t_cmd *cmd, t_free **ptr, t_expand **expand, t_cmd *h)
{
	char	*path;
	struct stat	state;

	ft_dup_file(cmd, h);
	if (ft_is_absolute_path(cmd->cmd))
	{
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
			if (g_global.shlvl == 0)
				ft_exp_add_back(expand, ft_exp_new("SHLVL=0", ptr));
		}
		if (access(cmd->cmd, X_OK | W_OK | R_OK | F_OK) == 0)
		{
			execve(cmd->cmd, cmd->arg, myenv(*expand, ptr));
			perror("");
		}
		else
			ft_cmd_not_found(cmd->cmd);
	}
	else
	{
		path = ft_found_path(g_global.split, cmd->cmd, ptr);
		if (g_global.split)
			ft_free_split(g_global.split);
		if (!path)
			ft_cmd_not_found(cmd->cmd);
		execve(path, cmd->arg, myenv(*expand, ptr));
		perror("");
	}
	exit(1);
}
