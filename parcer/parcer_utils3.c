/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:43:58 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 10:49:08 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (ft_entre_in_sigint(fd_in))
				return (1);
			break ;
		}
		if (ft_is_a_delemiter(input, tmp))
			break ;
		ft_expand_in_heredoc(input, main, &here, *tmp);
		ft_red_inheredoc(&here, &input, new);
	}
	return (dup2(fd_in, 0), close(fd_in), 0);
}

void	ft_check_space(t_token **tmp, int *i)
{
	while ((*tmp)->data[*i] && (((*tmp)->data[*i] >= 9
				&& (*tmp)->data[*i] <= 13) || (*tmp)->data[*i] == 32))
		(*i)++;
}

int	ft_check_ambiguous(t_token **tmp, int *file_fd)
{
	int	i;

	i = 0;
	ft_check_space(tmp, &i);
	if ((*tmp)->data[i] == '\0')
	{
		*file_fd = -1;
		ft_putstr_fd("minishell: : ambiguous redirect\n", 2);
		return (g_global.exit_global = 1, 1);
	}
	while ((*tmp)->data[i] && !(((*tmp)->data[i] >= 9
				&& (*tmp)->data[i] <= 13) || (*tmp)->data[i] == 32))
		i++;
	if ((*tmp)->data[i] == '\0')
		return (0);
	ft_check_space(tmp, &i);
	if ((*tmp)->data[i] == '\0')
		return (0);
	else
	{
		*file_fd = -1;
		ft_putstr_fd("minishell: : ambiguous redirect\n", 2);
		return (g_global.exit_global = 1, 1);
	}
	return (0);
}

void	ft_red_in(t_token **tmp, t_cmd **new, char **f)
{
	int	i;

	i = 0;
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
	if ((*tmp)->state == DOLLAR_SIGN)
	{
		if (ft_check_ambiguous(tmp, &((*new)->input)))
			return ;
	}
	(*new)->input = open((*tmp)->data, O_RDONLY, 0644);
	if ((*new)->input == -1)
	{
		(*new)->f = 1;
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
		if ((*new)->f)
			(*new)->input = -1;
	}
	if ((*tmp) && (*tmp)->type == RED_IN && !(*f))
	{
		(*new)->input != 0 && close((*new)->input);
		ft_red_in(tmp, new, f);
	}
	return (0);
}
