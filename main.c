/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:04 by nel-baz           #+#    #+#             */
/*   Updated: 2023/06/11 18:28:26 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	pop()
// {
// 	system("leaks minishell");
// }

int	main(int ac, char **av, char **env)
{
	char		*input_line;
	t_token		*token;
	t_free		*ptr;
	t_expand	*expand;

	// atexit(pop);
	(void)av;
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
			// ft_expanding(&token, expand, &ptr);
			while (token)
			{
				printf("`%s`\t%d\t%d\n", token->data, token->type, token->state);
				token = token->next;
			}
			ft_free(&ptr);
			free(input_line);
			// if (input_line[0] == ';')
			// 	exit(0);
		}
	}
	return (0);
}
