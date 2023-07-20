/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:50:15 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/20 10:37:22 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_word(t_token *token, t_free **newptr, char **args, int *i)
{
	int		j;
	char	**tmp;

	j = 0;
	if (token->state == DOLLAR_SIGN)
	{
		tmp = ft_split(token->data, ' ');
		ft_add_to_free(newptr, ft_new_node(tmp));
		while (tmp[j])
		{
			args[*i] = tmp[j];
			ft_add_to_free(newptr, ft_new_node(tmp[j]));
			(*i)++;
			j++;
		}
	}
	else
		args[(*i)++] = (token->data);
}

char	**ft_get_arg(t_token *token, t_free **newptr)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_malloc(newptr, (sizeof(char *) * (ft_len(token, newptr) + 1)));
	while (token && token->type != PIPE)
	{
		if (token->data && (token->type == RED_IN || token->type == RED_OUT
				|| token->type == RED_APP_OUT || token->type == HERE_DOC))
		{
			token = token->next;
			if (token->type == WHITE_SPACE)
				token = token->next;
			if (token->next)
				token = token->next;
			else
				break ;
			continue ;
		}
		if (token->data && token->type == WORD)
			ft_get_word(token, newptr, args, &i);
		token = token->next;
	}
	return (args[i] = NULL, args);
}

char	*check_existfile(void)
{
	static int	c;
	struct stat	state;
	char		*str;
	char		*ptr;

	str = ft_strdup("/tmp/here_doc");
	if (stat(str, &state) == 0)
	{
		ptr = ft_itoa(c);
		str = ft_strjoin(str, ptr);
		free (ptr);
		c++;
	}
	return (str);
}

void	ft_open_pipe(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		pipefd[2];

	tmp = *cmd;
	while (tmp && tmp->next)
	{
		pipe(pipefd);
		if (tmp->output == 1 || tmp->output == -1)
			tmp->output = pipefd[1];
		else
			close(pipefd[1]);
		if (tmp->next->input == 0 || tmp->input == -1)
			tmp->next->input = pipefd[0];
		else
			close(pipefd[0]);
		tmp = tmp->next;
	}
}
