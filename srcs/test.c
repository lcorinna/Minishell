/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/16 14:32:18 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_info				data;

	data = (t_info){};
	(void)argc;
	(void)argv;
	ft_envp(envp, &data);
	// ft_signal();
	while (!data.exit_f)
	{
		ft_readline("minishell$ " , &data);
		// printf("data.free_me.str - %s\n", str); //del в эту строку приходит то что мы подаем в наш Минишел
		if (!data.free_me.str) //обработка сигнала "control + d"
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
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