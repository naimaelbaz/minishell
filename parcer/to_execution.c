/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:39:41 by ylachhab          #+#    #+#             */
/*   Updated: 2023/06/13 19:28:19 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void print__(t_token *t);
t_cmd	*ft_new_cmd(t_free **ptr, char *content)
{
	t_cmd	*node;


	node = ft_malloc(ptr, sizeof(t_cmd));
	if (!node)
		return (NULL);
    node->cmd = content;
	node->input = 0;
	node->output = 1;
	node->next = NULL;
	return (node);
}

void	ft_add_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	ptr = *lst;
	if (!ptr)
	{
		*lst = new;
		return ;
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

// char	*ft_get_arg(t_token *token, t_free **ptr)
// {
// 	char	*join;

// 	join = NULL;
// 	while (token && token->type != PIPE)
// 	{
// 		if (token->data[0] == '>' || token->data[0] == '<')
// 		{
// 			token = token->next;
// 			if (token->type == WHITE_SPACE)
// 				token = token->next;
// 			if (token->next)
// 				token = token->next;
// 			else
// 				break ;
// 			continue ;
// 		}
// 		if (token->type != RED_APP_OUT && token->type != RED_IN
// 			&& token->type != RED_OUT && token->type != HERE_DOC
// 			&& token->type != WHITE_SPACE && token->type != PIPE)
// 		{
// 			join = ft_strjoin(join, token->data);
// 			join = ft_strjoin(join, " ");
// 		}
// 		if (token->type == PIPE)
// 			break ;
// 		token = token->next;
// 	}
// 	return (ft_add_to_free(ptr, ft_new_node(join)), join);
// }

int	ft_get_len(t_token *token)
{
	int	len;

	len = 0;
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
		if (token->type != RED_APP_OUT && token->type != RED_IN
			&& token->type != RED_OUT && token->type != HERE_DOC
			&& token->type != WHITE_SPACE && token->type != PIPE)
			len++;
		if (token->type == PIPE)
			break ;
		token = token->next;
	}
	return (len);
}

int	ft_count_pipe(t_token *token)
{
	int	p;

	p = 0;

	while (token)
	{
		if (token->type == PIPE)
			p++;
		token = token->next;
	}
	return (p);
}

char **split_args(t_token	*token)
{
	char **split;
	int	i;

	i = 0;
	split = malloc(sizeof(char *) * (ft_get_len(token) + 1));
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
		if (token->type != RED_APP_OUT && token->type != RED_IN
			&& token->type != RED_OUT && token->type != HERE_DOC
			&& token->type != WHITE_SPACE)
			split[i++] = token->data;
		token = token->next;
	}
	return(split[i] = NULL, split);
}

char	*ft_get_cmd(t_token *tmp)
{
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->data[0] == '>' || tmp->data[0] == '<')
		{
			tmp = tmp->next;
			if (tmp->type == WHITE_SPACE)
				tmp = tmp->next;
			if (tmp->next)
				tmp = tmp->next;
			else
				break ;
			continue ;
		}
		if (tmp->type != RED_APP_OUT && tmp->type != RED_IN
			&& tmp->type != RED_OUT && tmp->type != HERE_DOC
			&& tmp->type != WHITE_SPACE)
			return (tmp->data);
		tmp = tmp->next;
	}
	return(ft_strdup(""));
}

//TODO	printf
//TODO	HERE_DOC

void	ft_open_files(t_token **tmp, t_cmd **new)
{
	while ((*tmp) && (*tmp)->type != PIPE)
	{
		if ((*tmp) && (*tmp)->type == RED_IN)
		{
			(*tmp) = (*tmp)->next;
			if ((*tmp)->type == WHITE_SPACE)
				(*tmp) = (*tmp)->next;
			(*new)->input = open((*tmp)->data, O_RDONLY | O_TRUNC, 0644);
			if ((*new)->input == -1)
				printf(":%s: No such file or directory\n", (*tmp)->data);
		}
		else if ((*tmp) && (*tmp)->type == RED_OUT)
		{
			(*tmp) = (*tmp)->next;
			if ((*tmp)->type == WHITE_SPACE)
				(*tmp) = (*tmp)->next;
			(*new)->output = open((*tmp)->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if ((*new)->output == -1)
				perror("open");
		}
		else if ((*tmp) && (*tmp)->type == RED_APP_OUT)
		{
			(*tmp) = (*tmp)->next;
			if ((*tmp)->type == WHITE_SPACE)
				(*tmp) = (*tmp)->next;
			(*new)->output = open((*tmp)->data, O_CREAT | O_WRONLY, 0644);
		}
		// else if ((*tmp) && (*tmp)->type == HERE_DOC)
		// {
		// 	(*tmp) = (*tmp)->next;
		// 	if ((*tmp)->type == WHITE_SPACE)
		// 		(*tmp) = (*tmp)->next;
		// 	(*new)->output = open((*tmp)->data, O_CREAT | O_WRONLY, 0644);
		// }
		(*tmp) = (*tmp)->next;
	}
}

void print__(t_token *t)
{
	puts("-------");
	while (t)
	{
		puts(t->data);
		t = t->next;
	}
	puts("-------");
}

void	ft_parcer(t_token *token, t_cmd **cmd, t_free **ptr)
{
	t_cmd	*new;
	t_token	*tmp;
	int		i;
	int		countp;

	tmp = token;
	countp = ft_count_pipe(tmp) + 1;
	// print__(tmp);
	while (tmp)
	{
		if (countp > 0 && tmp->type != PIPE)
		{
			i = 0;
			new = ft_new_cmd(ptr, ft_strdup(ft_get_cmd(tmp)));

			 ft_add_cmd(cmd, new);
//			 new->arg = ft_split(ft_get_arg(tmp, ptr), ' ');
//			 while (new->arg[i])
//			 {
//			 	ft_add_to_free(ptr, ft_new_node(new->arg[i]));
//			 	i++;
//			 }
			new->arg = split_args(tmp);
			 ft_add_to_free(ptr, ft_new_node(new->arg));
			 ft_open_files(&tmp, &new);
			countp--;
			if (countp == 0)
				break ;
		}
		tmp = tmp->next;
	}
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
