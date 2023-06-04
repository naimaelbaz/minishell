/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:04 by nel-baz           #+#    #+#             */
/*   Updated: 2023/06/04 11:44:29 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char **av)
{
	char	*input_line;
	t_token	*token;
	t_free	*ptr;

	(void)av;
	if (ac == 1)
	{
		while (1)
		{
			token = NULL;
			ptr = NULL;
			input_line = readline("minishell$ ");
			if (!input_line)
				return (0);
			if (ft_strlen(input_line))
				add_history(input_line);
			ft_lexing(input_line, &token, &ptr);
			while (token)
			{
				printf("`%s`\t%d\t%d\n", token->data, token->type, token->state);
				token = token->next;
			}
			ft_free(&ptr);
			free(input_line);
		}
	}
	return (0);
}
