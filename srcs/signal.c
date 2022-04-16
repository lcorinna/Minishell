/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 14:23:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/16 14:24:17 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_signal_processing(int sig)
// {
// 	// rl_catch_signals = 0; //чтобы при вызове сигналов не выводилось "^C"
// 	if (sig == 2) // сигнал "control + c"
// 	{
// 		write(1, "\n", 1);
// 		rl_redisplay();
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 	}
// 	else if (sig == 3) // сигнал "control + \"
// 		(void)sig;
// }

// void	ft_signal(void)
// {
// 	struct sigaction	sa;
// 	struct termios		term;
// 	int					i;

// 	i = tcsetattr(STDIN_FILENO, TCSANOW, &term);
// 	printf("i - %d\n", i);
// 	i = tcgetattr(1, &term);
// 	printf("i - %d\n", i);
// 	sa.sa_handler = &ft_signal_processing;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigaction(SIGQUIT, &sa, NULL); //сигнал "control + \"
// 	sigaction(SIGINT, &sa, NULL); //сигнал "control + c"
// 	// signal(SIGINT, ft_signal_processing);
// 	// signal(SIGQUIT, ft_signal_processing);
// }
