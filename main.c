/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:04 by nel-baz           #+#    #+#             */
/*   Updated: 2023/07/09 19:06:00 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_global = 0;

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
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->data[0] == '\0' && tmp->state == DOLLAR_SIGN)
			tmp->data = NULL;
		tmp = tmp->next;
	}
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
		expand = ft_empty_env(&new_ptr);
	else if (env)
		expand = ft_get_env(&new_ptr, env);
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
			ft_builtins(cmd, &expand, &new_ptr);
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
