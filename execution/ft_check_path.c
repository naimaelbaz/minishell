/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:28:56 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 10:50:21 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_is_absolute_path(char *cmd)
{
	return (ft_strchr(cmd, '/'));
}

void	ft_cmd_not_found(char *cmd)
{
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
	if (cmd->input != 0 && cmd->f == 0)
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
	char		*path;

	ft_dup_file(cmd, h);
	if (ft_is_absolute_path(cmd->cmd))
	{
		ft_is_a_directory(cmd, ptr, expand);
		ft_exist_file(cmd);
		execve(cmd->cmd, cmd->arg, myenv(*expand, ptr));
		perror("");
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
