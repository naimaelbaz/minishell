/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:04 by nel-baz           #+#    #+#             */
/*   Updated: 2023/06/03 14:37:58 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*input;

	(void)av;
	(void)ac;
	if (ac != 1)
		return (printf("Error\n"), 1);
	while (1)
	{
		input = readline("minishell$ ");
		if (input)
			ft_check_syntax_error(input);
		if (strlen(input) > 0)
			add_history(input);
		free (input);
	}
}
