/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:04 by nel-baz           #+#    #+#             */
/*   Updated: 2023/07/13 09:00:43 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global = {0};

void	pop()
{
	system("leaks minishell");
}

int	ft_empty_arg(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i][0] != '\0')
			return (1);
		i++;
	}
	return (0);
}

void	ft_delete_empty_str(t_token **token)
{
	t_token	*tmp ;

	tmp = *token;
	while (tmp)
	{
		if (tmp->data[0] == '\0' && tmp->state == DOLLAR_SIGN)
			tmp->data = NULL;
		tmp = tmp->next;
	}
}

int	ft_expandsize(t_expand *lst)
{
	t_expand	*ptr;
	int			count;

	count = 0;
	if (!lst)
		return (0);
	ptr = NULL;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	return (count);
}

char	**myenv(t_expand *expand, t_free **ptr)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_malloc(ptr, sizeof(char *) * (ft_expandsize(expand) + 1));
	while (expand)
	{
		tmp[i] = ft_join(expand->key, "=");
		tmp[i] = ft_strjoin(tmp[i], expand->value);
		expand = expand->next;
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

int	main(int ac, char **av, char **env)
{
	char		*input_line;
	t_token		*token;
	t_free		*ptr;
	t_free		*new_ptr;
	t_expand	*expand;
	t_cmd		*cmd;

	// atexit(pop);
	(void)av;
	if (ac != 1)
		return (printf("Error\n"), 1);
	expand = NULL;
	new_ptr = NULL;
	if (env[0] == NULL)
	{
		g_global.path = 1;
		expand = ft_empty_env(&new_ptr);
	}
	else
		expand = ft_get_env(&new_ptr, env);
	g_global.shlvl = ft_atoi(ft_search_val("SHLVL", expand));
	if (g_global.shlvl >= 1000)
		g_global.shlvl = 0;
	ft_set_val("SHLVL", ft_itoa(g_global.shlvl + 1), &expand);
	while (1)
	{
		token = NULL;
		ptr = NULL;
		cmd = NULL;
		input_line = readline("minishell$ ");
		if (!input_line)
			exit(0);
		if (ft_strlen(input_line))
			add_history(input_line);
		if (ft_check_syntax_error(input_line))
		{
			ft_lexing(input_line, &token, &ptr);
			ft_expanding(&token, expand, &ptr);
			ft_delete(&token, &ptr);
			ft_join_string(&token, &ptr);
			ft_delete_empty_str(&token);
			ft_parcer(token, &cmd, &ptr, expand);
			ft_open_pipe(&cmd);
			ft_execution(cmd, &expand, &new_ptr, &ptr);
			// while (token)
			// {
			// 	printf("`%s`\t%d\t%d\n", token->data, token->type, token->state);
			// 	token = token->next;
			// }
			// if (input_line[0] == ';')
			// {
			// 	ft_free(&ptr);
			// 	exit(0);
			// }
		}
		ft_free(&ptr);
		free(input_line);
	}
	ft_free(&new_ptr);
	return (0);
}

