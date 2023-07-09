/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:21:17 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/09 13:10:22 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_expand *expand, int i)
{
	char	*str;

	while (expand)
	{
		if (i != 1 && expand->value)
		{
			str = ft_join(expand->key, "=");
			str = ft_strjoin(str, expand->value);
			ft_putstr_fd(str, i);
			ft_putstr_fd("\n", i);
			free (str);
		}
		else if (i == 1 && expand->value)
			printf("%s=%s\n", expand->key, expand->value);
		if (!expand->next)
			break ;
		expand = expand->next;
	}
}

void	ft_builtins(t_cmd *cmd, t_expand **expand, t_free **new_ptr)
{
	while (cmd)
	{
		if (!ft_strcmp(cmd->cmd, "pwd") && cmd->input != -1
			&& cmd->output != -1)
			ft_pwd(cmd->output);
		else if (!ft_strcmp(cmd->cmd, "env") && cmd->input != -1
			&& cmd->output != -1 && !cmd->arg[1])
			ft_env(*expand, cmd->output);
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
			ft_exit(cmd->arg, new_ptr);
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
}
