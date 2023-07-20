/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:24:48 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 10:52:27 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error_in_directory(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	ft_env(t_expand *expand, int i, char **arg)
{
	char	*str;

	if (arg[1])
	{
		ft_error_in_directory(arg[1]);
		g_global.exit_global = 127;
		return ;
	}
	while (expand && expand->value)
	{
		if (g_global.path && !ft_strcmp(expand->key, "PATH"))
		{
			expand = expand->next;
			continue ;
		}
		str = ft_join(expand->key, "=");
		str = ft_strjoin(str, expand->value);
		ft_putendl_fd(str, i);
		free (str);
		if (!expand->next)
			break ;
		expand = expand->next;
	}
	g_global.exit_global = 0;
}

void	ft_builtins(t_cmd *cmd, t_expand **expand, t_free **new_ptr, int flag)
{
	if (!ft_strcmp(cmd->cmd, "pwd") && cmd->input != -1
		&& cmd->output != -1)
		ft_pwd(cmd->output);
	else if (!ft_strcmp(cmd->cmd, "env") && cmd->input != -1
		&& cmd->output != -1)
		ft_env(*expand, cmd->output, cmd->arg);
	else if (!ft_strcmp(cmd->cmd, "echo") && cmd->input != -1
		&& cmd->output != -1)
		ft_echo(cmd->output, cmd->arg);
	else if (!ft_strcmp(cmd->cmd, "export") && cmd->input != -1
		&& cmd->output != -1 && !cmd->arg[1])
		ft_export(*expand, cmd->output, new_ptr);
	else if (!ft_strcmp(cmd->cmd, "export") && cmd->input != -1
		&& cmd->output != -1 && cmd->arg[1])
			*expand = ft_add_export(*expand, cmd->arg, new_ptr);
	else if (!ft_strcmp(cmd->cmd, "unset") && cmd->input != -1
		&& cmd->output != -1)
		*expand = ft_unset(cmd->arg, *expand);
	else if (!ft_strcmp(cmd->cmd, "cd") && cmd->input != -1
		&& cmd->output != -1)
		*expand = ft_cd(*expand, cmd->arg, new_ptr);
	else if (!ft_strcmp(cmd->cmd, "exit") && cmd->input != -1
		&& cmd->output != -1)
		ft_exit(cmd->arg, flag);
}

int	ft_check_built(t_cmd *cmd)
{
	if (cmd->input != -1 && cmd->output != -1
		&& ft_strcmp(cmd->cmd, "(null)") && ft_strcmp(cmd->cmd, "pwd")
		&& ft_strcmp(cmd->cmd, "env") && ft_strcmp(cmd->cmd, "echo")
		&& ft_strcmp(cmd->cmd, "export") && ft_strcmp(cmd->cmd, "unset")
		&& ft_strcmp(cmd->cmd, "cd") && ft_strcmp(cmd->cmd, "exit"))
		return (1);
	return (0);
}

void	ft_wait_process(t_cmd *h, pid_t	pid)
{
	int		status;

	ft_unlink_heredoc();
	while (h)
	{
		(h->input != 0) && close(h->input);
		(h->output != 1) && close(h->output);
		h = h->next;
	}
	waitpid(pid, &status, 0);
	while (waitpid(-1, 0, 0) != -1)
		;
	if (WIFEXITED(status))
		g_global.exit_global = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3 || WTERMSIG(status) == 2)
		{
			g_global.exit_global = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == 3)
				printf("Quit: %d\n", WTERMSIG(status));
			else
				printf("\n");
		}
	}
}
