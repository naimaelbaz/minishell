/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:44:04 by nel-baz           #+#    #+#             */
/*   Updated: 2023/07/17 16:55:25 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global = {0};

void	pop()
{
	system("leaks minishell");
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
		ft_execution(main->cmd, &main->expand, &main->new_ptr, &main->ptr);
		// while (main->token)
		// {
		// 	printf("`%s`\t%d\t%d\n", main->token->data, main->token->type, main->token->state);
		// 	main->token = main->token->next;
		// }
		// exit (1);
	}
	ft_free(&main->ptr);
	free(input_line);
	return (1);
}

void	ft_put_env(t_main *main, char **env)
{
	if (env[0] == NULL)
	{
		g_global.path = 1;
		main->expand = ft_empty_env(&main->new_ptr);
	}
	else
		main->expand = ft_get_env(&main->new_ptr, env);
	g_global.shlvl = ft_atoi(ft_search_val("SHLVL", main->expand));
	if (g_global.shlvl == 999)
	{
		ft_set_val("SHLVL", "", &main->expand);
		return ;
	}
	if (g_global.shlvl >= 1000)
		g_global.shlvl = 0;
	ft_set_val("SHLVL", ft_itoa(g_global.shlvl + 1), &main->expand);
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

int	main(int ac, char **av, char **env)
{
	char		*input_line;
	t_main		main;
	// int			fd_in;

	// atexit(pop);
	(void)av;
	if (ac != 1)
		return (printf("Error\n"), 1);
	main.expand = NULL;
	main.new_ptr = NULL;
	ft_put_env(&main, env);
	signal(SIGQUIT, SIG_IGN);
	// fd_in = dup(0);
	while (1)
	{
		main.token = NULL;
		main.ptr = NULL;
		main.cmd = NULL;
		rl_catch_signals = 0;
		signal(SIGINT, ft_handle_sigint);
		input_line = readline("minishell$ ");
		// if (!isatty(0))
		// {
			// dup2(fd_in, 0);
		// 	ft_free(&main.ptr);
		// 	continue ;
		// }
		if (!input_line)
		{
			printf("\033[1A\033[12Cexit\n");
			// close(fd_in);
			exit (0);
		}
		if (ft_strlen(input_line))
			add_history(input_line);
		if (!ft_functions(&main, input_line))
			continue;
		// if (input_line[0] == ';')
		// {
		// 	ft_free(&main.ptr);
		// 	exit(0);

		// }
	}
	ft_free(&main.new_ptr);
	return (0);
}
