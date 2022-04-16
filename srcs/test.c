/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/16 19:52:05 by lcorinna         ###   ########.fr       */
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
		ft_readline(&data);
		if (!data.free_me.str) //обработка сигнала "control + d"
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		// lexer
		// parser
		
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