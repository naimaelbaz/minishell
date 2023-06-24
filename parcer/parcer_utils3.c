/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:43:58 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/24 18:41:21 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_put_infile(t_token **tmp, t_cmd **new, t_expand *expand)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (!ft_strcmp(input, (*tmp)->data))
		{
			free(input);
			break ;
		}
		if ((*tmp)->state != IN_D_QOUTE && (*tmp)->state != IN_QOUTE)
			ft_expand_in_heredoc(&input, expand);
		ft_putstr_fd(input, (*new)->input);
		ft_putstr_fd("\n", (*new)->input);
		free (input);
	}
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
		return ;
	}
	(*new)->input = open((*tmp)->data, O_RDONLY | O_TRUNC, 0644);
	(*new)->input == -1 && ((*f) = (*tmp)->data);
}

void	ft_input_red(t_token **tmp, t_cmd **new, t_expand *expand, char **f)
{
	char	*str;
	int		i;

	i = 0;
	if ((*tmp) && (*tmp)->type == HERE_DOC)
	{
		i == 1 && close((*new)->input);
		(*tmp) = (*tmp)->next;
		if ((*tmp)->type == WHITE_SPACE)
			(*tmp) = (*tmp)->next;
		str = check_existfile();
		(*new)->input = open(str, O_CREAT | O_RDWR, 0644);
		ft_put_infile(tmp, new, expand);
		free(str);
		i = 1;
	}
	if ((*tmp) && (*tmp)->type == RED_IN && !(*f))
	{
		i == 1 && close((*new)->input);
		ft_red_in(tmp, new, f);
		i = 1;
	}
}
