/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/09 19:14:00 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


// static void	handler(int signal)
// {
// 	// rl_on_new_line();
// 	// // rl_replace_line();
// 	// rl_redisplay();
// 	printf("signal %d\n", signal); //del
// 	if (signal == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else
// 		exit(11);
// 	// else
// 		// write(1, "  \b\b", 4);
// }

void	ft_signal_processing(int sig)
{
	printf("%d\n", sig);
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_redisplay();
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (sig == 3)
		sig = 3;
	else if (sig == 15)
		exit (0);
	// exit (0);
	// minishell$
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	char				*str;

	sa.sa_handler = &ft_signal_processing;
	sa.sa_flags = SA_SIGINFO;
	// signal(SIGINT, handler);
	// signal(SIGTERM, handler);
	sigaction(SIGINT, &sa, NULL); //  сигнал "control + c"
	sigaction(SIGQUIT, &sa, NULL); // сигнал "control + \"
	// sigaction(SIGTERM, &sa, NULL); // сигнал "control + d" не обрабатывать
	ft_envp(envp);
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			ft_putstr_fd("exit\n", 1);
			break;
		}
		signal(SIGINT, &ft_signal_processing);
		// signal(SIGQUIT, SIG_IGN);
		// signal(SIGTERM, SIG_IGN);
	}
	ft_clean_struct(lalala);
	argc = 0;
	argv = NULL;
	envp = NULL;
	return (0);
}

// 1. инициализация структур
// 2. цикл (1)
// 	2.1 ридлайн
// 	2.2 лексер
// 	2.3 парсер
// 	2.4 экзекве
// 3. диструктор

// struct env
// char * key
// char * value

// gcc -lreadline test.c && ./a.out