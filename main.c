/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:04 by nel-baz           #+#    #+#             */
/*   Updated: 2023/07/20 08:35:38 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global = {0};

int	ft_functions(t_main	*main, char *input_line)
{
	if (ft_check_syntax_error(input_line))
	{
		ft_lexing(input_line, &main->token, &main->ptr);
		ft_expanding(&main->token, main->expand, &main->ptr, 0);
		ft_delete(&main->token, &main->ptr);
		ft_join_string(&main->token, &main->ptr);
		ft_delete_empty_str(&main->token);
		if (ft_parcer(&main))
		{
			ft_free(&main->ptr);
			free(input_line);
			return (0);
		}
		ft_open_pipe(&main->cmd);
		ft_execution(main);
	}
	ft_free(&main->ptr);
	free(input_line);
	return (1);
}

void	ft_handle_sigint(int sig)
{
	(void)sig;
	if (waitpid(-1, 0, WNOHANG) == 0)
		return ;
	g_global.exit_global = 1;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_init_var(t_main *main, int flag)
{
	if (flag)
	{
		main->token = NULL;
		main->ptr = NULL;
		main->cmd = NULL;
	}
	else
	{
		main->expand = NULL;
		main->new_ptr = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	char		*input_line;
	t_main		main;

	(void)av;
	if (ac != 1)
		return (printf("Error\n"), 1);
	ft_put_env(&main, env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ft_init_var(&main, 1);
		rl_catch_signals = 0;
		signal(SIGINT, ft_handle_sigint);
		input_line = readline("minishell$ ");
		if (!input_line)
		{
			printf("exit\n");
			exit (0);
		}
		if (ft_strlen(input_line))
			add_history(input_line);
		if (!ft_functions(&main, input_line))
			continue ;
	}
	return (ft_free(&main.new_ptr), 0);
}
