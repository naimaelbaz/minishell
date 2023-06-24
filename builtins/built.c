/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:21:17 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/24 20:28:23 by ylachhab         ###   ########.fr       */
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

int	ft_check_syntax_unset(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	check_exist_var(char *arg, t_expand **expand)
{
	t_expand	*tmp;

	tmp = *expand;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, arg))
		{
			if (tmp->prev == NULL && !tmp->next)
			{
				*expand = NULL;
				break ;
			}
			if (tmp->prev == NULL)
			{
				*expand = (*expand)->next;
				(*expand)->prev = NULL;
				tmp = *expand;
				continue ;
			}
			if (!tmp->next)
			{
				tmp->prev->next = NULL;
				break ;
			}
			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
		}
		tmp = tmp->next;
	}
}

char *ft_search_val(char *key, t_expand	*expand)
{
	while (expand)
	{
		if (!ft_strcmp(expand->key, key))
			return (expand->value);
		expand = expand->next;
	}
	return (NULL);
}

void	ft_set_val(char *key, char *value, t_expand **expand)
{
	t_expand	*tmp;

	tmp = *expand;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			tmp->value = value;
			break ;
		}
		tmp = tmp->next;
	}
}


t_expand	*ft_cd(t_expand *expand)
{
	if (chdir(ft_search_val("HOME", expand)) == 0)
	{
		if (ft_search_val("PWD", expand))
			ft_set_val("OLDPWD", ft_search_val("PWD", expand), &expand);
		ft_set_val("PWD", ft_search_val("HOME", expand), &expand);
	}
	else
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	return (expand);
}

t_expand	*ft_unset(char	**arg, t_expand *expand)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if ((!ft_isalpha(arg[i][0]) && arg[i][0] != '_') || !ft_check_syntax_unset(arg[i]))
		{
			ft_print_error(arg[i]);
			i++;
			continue ;
		}
		check_exist_var(arg[i], &expand);
		i++;
	}
	return (expand);
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
			&& cmd->output != -1 && !cmd->arg[1])
			*expand = ft_cd(*expand);
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
