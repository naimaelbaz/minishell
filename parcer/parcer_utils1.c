/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:50:15 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/15 19:40:48 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_get_arg(t_token *token, t_free **newptr)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_malloc(newptr, (sizeof(char *) * (ft_len(token) + 1)));
	while (token && token->type != PIPE)
	{
		if (token->data[0] == '>' || token->data[0] == '<')
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
		if (token->type == WORD)
			args[i++] = (token->data);
		token = token->next;
	}
	return (args[i] = NULL, args);
}

char	*check_existfile(void)
{
	static int	c;
	struct stat	state;
	char		*str;

	str = "/tmp/here_doc";
	if (stat(str, &state) == 0)
		str = ft_join(str, ft_itoa(c++));
	return (str);
}

void	ft_expand_here_doc(char **str, t_expand *expand)
{
	if (ft_isdigit((*str)[1]))
	{
		*str += 2;
		*str = ft_substr(*str, 0, ft_strlen(*str));
	}
	else
		*str = ft_get_value(*str, expand, 0);
}

void	ft_expand_in_heredoc(char **input, t_expand	*expand)
{
	if ((*input)[0] == '$' && ((*input)[1] != '\0' && (*input)[1] != '?'))
		ft_expand_here_doc(input, expand);
}

void	ft_open_pipe(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		pipefd[2];

	tmp = *cmd;
	while (tmp && tmp->next)
	{
		pipe(pipefd);
		if (tmp->output == 1)
			tmp->output = pipefd[1];
		if (tmp->next->input == 0)
			tmp->next->input = pipefd[0];
		tmp = tmp->next;
	}
}
