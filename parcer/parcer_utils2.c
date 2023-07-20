/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:39:26 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 10:49:59 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_red_inheredoc(t_token **here, char **input, t_cmd **new)
{
	while (*here)
	{
		ft_putstr_fd((*here)->data, (*new)->input);
		(*here) = (*here)->next;
	}
	ft_putstr_fd("\n", (*new)->input);
	free (*input);
}

void	ft_no_file(char **f)
{
	if (*f)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*f, 2);
		ft_putstr_fd(": ", 2);
		if (access(*f, F_OK) == -1)
			ft_putstr_fd("No such file or directory\n", 2);
		else if (access(*f, X_OK | W_OK | R_OK) == -1)
			ft_putstr_fd("Permission denied\n", 2);
		else
			ft_putendl_fd(strerror(errno), 2);
		g_global.exit_global = 1;
	}
}

void	ft_red_app_out(t_token **tmp, t_cmd **new, char **f)
{
	(*tmp) = (*tmp)->next;
	if ((*tmp)->type == WHITE_SPACE)
		(*tmp) = (*tmp)->next;
	if (!(*tmp)->data && (*tmp)->state == DOLLAR_SIGN)
	{
		(*new)->output = -1;
		ft_putendl_fd("minishell: : ambiguous redirect", 2);
		g_global.exit_global = 1;
		return ;
	}
	if ((*tmp)->state == DOLLAR_SIGN)
	{
		if (ft_check_ambiguous(tmp, &((*new)->output)))
			return ;
	}
	(*new)->output = open((*tmp)->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	(*new)->output == -1 && ((*f) = (*tmp)->data);
}

void	ft_output_red(t_token **tmp, t_cmd **new, char **f, int *p)
{
	if ((*tmp) && (*tmp)->type == RED_OUT && !(*f))
	{
		(*new)->output != 1 && close((*new)->output);
		(*tmp) = (*tmp)->next;
		((*tmp)->type == WHITE_SPACE) && ((*tmp) = (*tmp)->next);
		if (ft_ambiguous(tmp, new))
			return ;
		if (ft_is_pipe(tmp, new, p))
			return ;
		if ((*new)->output == -1)
		{
			((*f) = (*tmp)->data);
			g_global.exit_global = 1;
		}
	}
	else if ((*tmp) && (*tmp)->type == RED_APP_OUT && !(*f))
	{
		(*new)->output != 1 && close((*new)->output);
		ft_red_app_out(tmp, new, f);
	}
}

int	ft_open_files(t_token **tmp, t_cmd **new, t_main **main, int *p)
{
	char	*f;

	f = NULL;
	g_global.exit_global = 0;
	while ((*tmp) && (*tmp)->type != PIPE)
	{
		if (ft_input_red(tmp, new, main, &f))
			return (1);
		ft_output_red(tmp, new, &f, p);
		(*tmp) = (*tmp)->next;
	}
	ft_no_file(&f);
	return (0);
}
