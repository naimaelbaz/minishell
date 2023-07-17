/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:43:58 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/17 16:54:28 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ambiguous(t_token **tmp, t_cmd **new)
{
	if (!(*tmp)->data && (*tmp)->state == DOLLAR_SIGN)
	{
		(*new)->output = -1;
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_global.exit_global = 1;
		return (1);
	}
	return (0);
}

int	ft_is_pipe(t_token **tmp, t_cmd **new, int	*p)
{
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

void	ft_handle_heredoc(int sig)
{
	(void)sig;
	close(0);
	g_global.here_sig = 1;
	g_global.exit_global = 1;
	// rl_replace_line("", 0);
	// rl_on_new_line();
}

int	ft_put_infile(t_token **tmp, t_cmd **new, t_main **main)
{
	char		*input;
	t_token		*here;
	int			fd_in;

	fd_in = dup(0);
	g_global.here_sig = 0;
	signal(SIGINT, ft_handle_heredoc);
	while (1)
	{
		here = NULL;
		input = readline("> ");
		if (!input)
		{
			if (g_global.here_sig)
			{
				dup2(fd_in, 0);
				ft_unlink_heredoc();
				close(fd_in);
				return (1);
			}
			break ;
		}
		if (!ft_strcmp(input, (*tmp)->data))
		{
			free(input);
			break ;
		}
		ft_expand_in_heredoc(input, main, &here, *tmp);
		while (here)
		{
			ft_putstr_fd((here)->data, (*new)->input);
			(here) = (here)->next;
		}
		ft_putstr_fd("\n", (*new)->input);
		free (input);
	}
	dup2(fd_in, 0);
	close(fd_in);
	return (0);
}

void	ft_red_in(t_token **tmp, t_cmd **new, char **f)
{
	(*tmp) = (*tmp)->next;
	if ((*tmp)->type == WHITE_SPACE)
		(*tmp) = (*tmp)->next;
	if (!(*tmp)->data && (*tmp)->state == DOLLAR_SIGN)
	{
		(*new)->input = -1;
		ft_putstr_fd("minishell: : ambiguous redirect\n", 2);
		g_global.exit_global = 1;
		return ;
	}
	(*new)->input = open((*tmp)->data, O_RDONLY, 0644);
	if ((*new)->input == -1)
	{
		g_global.input = 1;
		((*f) = (*tmp)->data);
		g_global.exit_global = 1;
	}
}

int	ft_input_red(t_token **tmp, t_cmd **new, t_main **main, char **f)
{
	if ((*tmp) && (*tmp)->type == HERE_DOC)
	{
		(*new)->input != 0 && close((*new)->input);
		ft_unlink_heredoc();
		(*tmp) = (*tmp)->next;
		if ((*tmp)->type == WHITE_SPACE)
			(*tmp) = (*tmp)->next;
		g_global.name_hedoc = check_existfile();
		(*new)->input = open(g_global.name_hedoc, O_CREAT | O_RDWR, 0644);
		g_global.hedoc = (*new)->input;
		if (ft_put_infile(tmp, new, main))
			return (1);
		close((*new)->input);
		(*new)->input = open(g_global.name_hedoc, O_CREAT | O_RDWR, 0644);
		if (g_global.input)
			(*new)->input = -1;
	}
	if ((*tmp) && (*tmp)->type == RED_IN && !(*f))
	{
		(*new)->input != 0 && close((*new)->input);
		ft_red_in(tmp, new, f);
	}
	return (0);
}
