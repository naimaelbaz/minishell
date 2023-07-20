/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:21:17 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 09:55:53 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handle_sigquit(int sig)
{
	(void)sig;
}

void	ft_handle(t_cmd **cmd, t_expand **expand)
{
	signal(SIGQUIT, ft_handle_sigquit);
	if ((*cmd)->cmd[0] == '\0')
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		(*cmd) = (*cmd)->next;
		exit(127);
	}
	g_global.split = ft_split_path(*expand);
}

void	ft_exec_cmd(t_main *main, t_cmd *h)
{
	if (!ft_check_built(main->cmd))
	{
		ft_builtins(main->cmd, &main->expand, &main->new_ptr, 1);
		exit (g_global.exit_global);
	}
	else if (ft_check_built(main->cmd))
		to_be_executed(main->cmd, &main->ptr, &main->expand, h);
}

void	cmd_func(t_main *main, t_cmd *h)
{
	ft_handle(&main->cmd, &main->expand);
	ft_exec_cmd(main, h);
}

void	ft_execution(t_main *main)
{
	t_cmd	*h;
	pid_t	pid;

	h = main->cmd;
	while (main->cmd)
	{
		if (main->cmd && !ft_check_built(main->cmd)
			&& !main->cmd->next && !main->cmd->prev)
			ft_builtins(main->cmd, &main->expand, &main->new_ptr, 0);
		else if (main->cmd && ft_strcmp(main->cmd->cmd, "(null)"))
		{
			pid = fork();
			if (pid == 0)
				cmd_func(main, h);
			else if (pid < 0)
			{
				perror("");
				return ;
			}
		}
		main->cmd = main->cmd->next;
	}
	ft_wait_process(h, pid);
}
