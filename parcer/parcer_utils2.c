/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:39:26 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/15 19:42:38 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_no_file(char *f)
{
	char	*st;

	if (f)
	{
		st = ft_join(f, ": No such file or directory\n");
		ft_putstr_fd(st, 2);
		free (st);
	}
}

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
	}
}

void	ft_input_red(t_token **tmp, t_cmd **new, t_expand *expand, char *f)
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
		i = 1;
	}
	if ((*tmp) && (*tmp)->type == RED_IN && !f)
	{
		i == 1 && close((*new)->input);
		(*tmp) = (*tmp)->next;
		if ((*tmp)->type == WHITE_SPACE)
			(*tmp) = (*tmp)->next;
		(*new)->input = open((*tmp)->data, O_RDONLY | O_TRUNC, 0644);
		(*new)->input == -1 && (f = (*tmp)->data);
		i = 1;
	}
}

void	ft_output_red(t_token **tmp, t_cmd **new, char *f)
{
	int	j;

	j = 0;
	if ((*tmp) && (*tmp)->type == RED_OUT && !f)
	{
		j == 1 && close((*new)->output);
		(*tmp) = (*tmp)->next;
		if ((*tmp)->type == WHITE_SPACE)
			(*tmp) = (*tmp)->next;
		(*new)->output = open((*tmp)->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		j = 1;
	}
	else if ((*tmp) && (*tmp)->type == RED_APP_OUT && !f)
	{
		j == 1 && close((*new)->output);
		(*tmp) = (*tmp)->next;
		if ((*tmp)->type == WHITE_SPACE)
			(*tmp) = (*tmp)->next;
		(*new)->output = open((*tmp)->data, O_CREAT | O_WRONLY, 0644);
		j = 1;
	}
}

void	ft_open_files(t_token **tmp, t_cmd **new, t_expand *expand)
{
	char	*f;

	f = NULL;
	while ((*tmp) && (*tmp)->type != PIPE)
	{
		ft_input_red(tmp, new, expand, f);
		ft_output_red(tmp, new, f);
		(*tmp) = (*tmp)->next;
	}
	ft_no_file(f);
}
