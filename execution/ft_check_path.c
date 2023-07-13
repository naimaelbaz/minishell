/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:28:56 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/13 09:33:03 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_absolute_path(char *cmd)
{
	return (cmd[0] == '/' || cmd[0] == '.');
}

void	ft_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minshell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_global.exit_global = 127;
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
	if (cmd->input != 0)
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

	ft_dup_file(cmd, h);
	if (ft_is_absolute_path(cmd->cmd))
	{
		if (ft_strcmp(cmd->cmd, ".") && ft_strcmp(cmd->cmd, "..")
			&& access(cmd->cmd, X_OK) == 0)
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
