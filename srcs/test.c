/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/13 22:19:36 by merlich          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_info				data;
	char				*str;

	data = (t_info){};
	(void)argc;
	(void)argv;
	data.envp = envp;
	// ft_signal();
	while (!data.exit_f)
	{
		str = ft_readline("minishell$ " , &data);  // А: Немного прокачал readline
		printf("str - %s\n", str); //del в эту строку приходит то что мы подаем в наш Минишел
		if (!str) //обработка сигнала "control + d"
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		// add_history(str);  // del A: Немного прокачал readline
	}
	// ft_clean_struct(lalala);
	return (0);
}

// 1. инициализация структур
// 2. цикл (1)
// 	2.1 ридлайн
// 	2.2 лексер
// 	2.3 парсер
// 	2.4 экзекве
// 3. деструктор

// struct env
// char * key
// char * value

// gcc -lreadline test.c && ./a.out