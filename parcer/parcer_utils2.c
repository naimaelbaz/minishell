/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:39:26 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/08 11:23:09 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_no_file(char **f)
{
	if (*f)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*f, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
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
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		return ;
	}
	(*new)->output = open((*tmp)->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	(*new)->output == -1 && ((*f) = (*tmp)->data);
}

void	ft_output_red(t_token **tmp, t_cmd **new, char **f, int *p)
{
	int	j;

	j = 0;
	if ((*tmp) && (*tmp)->type == RED_OUT && !(*f))
	{
		j == 1 && close((*new)->output);
		(*tmp) = (*tmp)->next;
		if ((*tmp)->type == WHITE_SPACE)
			(*tmp) = (*tmp)->next;
		if (ft_ambiguous(tmp, new))
			return ;
		if (ft_is_pipe(tmp, new, p))
			return ;
		(*new)->output == -1 && ((*f) = (*tmp)->data);
		j = 1;
	}
	else if ((*tmp) && (*tmp)->type == RED_APP_OUT && !(*f))
	{
		j == 1 && close((*new)->output);
		ft_red_app_out(tmp, new, f);
		j = 1;
	}
}

void	ft_open_files(t_token **tmp, t_cmd **new, t_expand *expand, int *p)
{
	char	*f;

	f = NULL;
	while ((*tmp) && (*tmp)->type != PIPE)
	{
		ft_input_red(tmp, new, expand, &f);
		ft_output_red(tmp, new, &f, p);
		(*tmp) = (*tmp)->next;
	}
	ft_no_file(&f);
}
