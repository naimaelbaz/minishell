/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:21:17 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/13 08:55:29 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_expand *expand, int i, char **arg)
{
	char	*str;

	if (arg[1])
	{
		ft_printf_error(arg[1]);
		g_global.exit_global = 127;
		return ;
	}
	while (expand)
	{
		if (i != 1 && expand->value)
		{
			if (g_global.path && !ft_strcmp(expand->key, "PATH"))
			{
				expand = expand->next;
				continue ;
			}
			str = ft_join(expand->key, "=");
			str = ft_strjoin(str, expand->value);
			ft_putstr_fd(str, i);
			ft_putstr_fd("\n", i);
			free (str);
		}
		else if (i == 1 && expand->value)
		{
			if (g_global.path && !ft_strcmp(expand->key, "PATH"))
			{
				expand = expand->next;
				continue ;
			}
			printf("%s=%s\n", expand->key, expand->value);
		}
		if (!expand->next)
			break ;
		expand = expand->next;
	}
	g_global.exit_global = 0;
}

void	ft_builtins(t_cmd *cmd, t_expand **expand, t_free **new_ptr)
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
		ft_exit(cmd->arg);
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

void	ft_wait_process(t_cmd *h)
{
	int		status;

	while (h)
	{
		(h->input != 0) && close(h->input);
		(h->output != 1) && close(h->output);
		h = h->next;
	}
	while (waitpid(-1, &status, 0) != -1)
		;
	if (status && WIFEXITED(status))
		g_global.exit_global = WEXITSTATUS(status);
}

void	ft_execution(t_cmd *cmd, t_expand **expand, t_free **new_ptr,
		t_free **ptr)
{
	char	**split;
	t_cmd	*h;
	pid_t	pid;

	h = cmd;
	while (cmd)
	{
		if (!ft_check_built(cmd))
			ft_builtins(cmd, expand, new_ptr);
		else if (ft_check_built(cmd))
		{
			pid = fork();
			if (pid == 0)
			{
				split = ft_split_path(*expand);
				to_be_executed(cmd, ptr, split, expand, h);
			}
			if (pid < 0)
			{
				perror("");
				return ;
			}
		}
		// int i = 0;
		// printf("`%s`\t%d\t%d\n", cmd->cmd, cmd->input, cmd->output);
		// while (cmd->arg[i])
		// {
		// 	printf("[%s] ", cmd->arg[i]);
		// 	i++;
		// }
		// printf("\n");
		cmd = cmd->next;
	}
	ft_wait_process(h);
}
