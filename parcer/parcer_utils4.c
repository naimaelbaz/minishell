/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 08:23:31 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/19 08:05:29 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_a_delemiter(char *input, t_token **tmp)
{
	if (!ft_strcmp(input, (*tmp)->data))
	{
		free(input);
		return (1);
	}
	return (0);
}

int	ft_is_pipe(t_token **tmp, t_cmd **new, int	*p)
{
	int	i;

	i = 0;
	if ((*tmp)->type == PIPE)
	{
		(*p)--;
		(*tmp) = (*tmp)->next;
		if ((*tmp)->type == WHITE_SPACE)
			(*tmp) = (*tmp)->next;
		if (ft_ambiguous(tmp, new))
			return (1);
		(*new)->output = open((*tmp)->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
		(*new)->output = open((*tmp)->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (0);
}

int	ft_ambiguous(t_token **tmp, t_cmd **new)
{
	if (!(*tmp)->data && (*tmp)->state == DOLLAR_SIGN)
	{
		(*new)->output = -1;
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_global.exit_global = 1;
		return (1);
	}
	if ((*tmp)->state == DOLLAR_SIGN)
	{
		if (ft_check_ambiguous(tmp, &((*new)->input)))
			return (1);
	}
	return (0);
}

void	ft_handle_heredoc(int sig)
{
	(void)sig;
	close(0);
	g_global.here_sig = 1;
	g_global.exit_global = 1;
}

int	ft_entre_in_sigint(int fd_in)
{
	if (g_global.here_sig)
	{
		dup2(fd_in, 0);
		ft_unlink_heredoc();
		close(fd_in);
		return (1);
	}
	return (0);
}
