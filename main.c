/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:04 by nel-baz           #+#    #+#             */
/*   Updated: 2023/06/13 19:17:42 by ylachhab         ###   ########.fr       */
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

	atexit(pop);
	(void)av;
	if (ac != 1)
		return (printf("Error\n"), 1);
	while (1)
	{
		token = NULL;
		ptr = NULL;
		cmd = NULL;
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
//			ft_delete(&token, &ptr);
			ft_join_string(&token);
			// char **s = split_args(token);
			// int i = 0;
			// while (s[i])
			// {
			// 	printf("[%s] ", s[i]);
			// 	i++;
			// }
			// printf("\n");
			// ft_get_arg(token, &ptr);
			// printf("%d\n", ft_count_pipe(token));
			ft_parcer(token, &cmd, &ptr);
			// ft_open_pipe(&cmd);
			 while (cmd)
			 {
			 	int i = 0;
			 	printf("`%s`\t%d\t%d\n", cmd->cmd, cmd->input, cmd->output);
			 	while (cmd->arg[i])
			 	{
			 		printf("[%s] ", cmd->arg[i]);
			 	// printf("-> %s\n", cmd->arg[i] ? cmd->arg[i] : "NIL");
			 		i++;
			 	}
			 	printf("\n");
			 	cmd = cmd->next;
			 }
//			while (token)
//			{
//				printf("`%s`\t%d\t%d\n", token->data, token->type, token->state);
//				token = token->next;
//			}
			ft_free(&ptr);
			free(input_line);
			if (input_line[0] == ';')
				exit(0);
			// token = NULL;
		}
	}
	return (0);
}
