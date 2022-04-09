/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/09 17:09:05 by lcorinna         ###   ########.fr       */
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
	// printf("%d\n", sig);
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

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_signal_processing;
	sa.sa_flags = SA_SIGINFO;
	// signal(SIGINT, handler);
	// signal(SIGTERM, handler);
	sigaction(SIGINT, &sa, NULL); // "c"
	sigaction(SIGQUIT, &sa, NULL); // "\"
	sigaction(SIGTERM, &sa, NULL); // "d"
	while (1)
	{
		readline("minishell$ ");
		signal(SIGINT, &ft_signal_processing);
		// signal(SIGQUIT, SIG_IGN);
		// signal(SIGTERM, SIG_IGN);
	}
	argc = 0;
	argv = NULL;
	return (0);
}

// gcc -lreadline test.c && ./a.out