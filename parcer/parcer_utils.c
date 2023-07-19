/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:39:41 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/18 14:58:59 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_getlen(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != ' ')
	{
		i++;
		len++;
	}
	return (len);
}

char	*ft_ret_cmd(t_token *token, t_free **ptr)
{
	char	*str;
	int		i;

	i = 0;
	if (token->state == DOLLAR_SIGN)
	{
		while (token->data[i] && token->data[i] == ' ')
			i++;
		str = ft_substr(token->data, i, ft_getlen(token->data, i));
		ft_add_to_free (ptr, ft_new_node(str));
		return (str);
	}
	else
		return (token->data);
}

char	*ft_get_cmd(t_token	*token, t_free **ptr)
{
	while (token && token->type != PIPE)
	{
		if (token->data && (token->type == RED_IN || token->type == RED_OUT
				|| token->type == RED_APP_OUT || token->type == HERE_DOC))
		{
			token = token->next;
			if (token && token->type == WHITE_SPACE)
				token = token->next;
			if (token->next)
				token = token->next;
			else
				break ;
			continue ;
		}
		if (token->data && token->type == WORD)
			return (ft_ret_cmd(token, ptr));
		token = token->next;
	}
	return ("(null)");
}

void	ft_return_len(t_token *token, t_free **newptr, int *len)
{
	char	**tmp;
	int		i;

	i = 0;
	if (token->state == DOLLAR_SIGN)
	{
		tmp = ft_split(token->data, ' ');
		ft_add_to_free(newptr, ft_new_node(tmp));
		while (tmp[i])
		{
			ft_add_to_free(newptr, ft_new_node(tmp[i]));
			i++;
			(*len)++;
		}
	}
	else
		(*len)++;
}

int	ft_len(t_token *token, t_free **newptr)
{
	int	len;

	len = 0;
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
			ft_return_len(token, newptr, &len);
		token = token->next;
	}
	return (len);
}
