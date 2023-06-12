/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:04 by nel-baz           #+#    #+#             */
/*   Updated: 2023/06/12 16:02:20 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	char		*input_line;
	t_token		*token;
	t_free		*ptr;
	t_expand	*expand;
	t_cmd		*cmd;

	// atexit(pop);
	(void)av;
	cmd = NULL;
	token = NULL;
	ptr = NULL;
	if (ac != 1)
		return (printf("Error\n"), 1);
	while (1)
	{
		input_line = readline("minishell$ ");
		if (!input_line)
			return (0);
		if (ft_strlen(input_line))
			add_history(input_line);
		if (ft_check_syntax_error(input_line))
		{
			ft_lexing(input_line, &token, &ptr);
			expand = ft_get_env(&ptr, env);
			ft_expanding(&token, expand, &ptr);
			ft_delete(&token, &ptr);
			ft_join_string(&token);
			ft_parcer(token, &cmd, &ptr);
			while (cmd)
			{
				printf("`%s`\t%d\t%d\t%s\n", cmd->cmd, cmd->input, cmd->output, cmd->arg[0]);
				cmd = cmd->next;
			}
			// while (token)
			// {
			// 	printf("`%s`\t%d\t%d\n", token->data, token->type, token->state);
			// 	token = token->next;
			// }
			ft_free(&ptr);
			free(input_line);
			// if (input_line[0] == ';')
			// 	exit(0);
		}
	}
	return (0);
}
