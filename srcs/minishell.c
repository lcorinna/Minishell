/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/11 21:26:17 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_info				data;

	data = (t_info){};

	ft_transfer(argc, argv, envp, &data);
	// ft_signal(); //буду делать в конце
	while (!data.exit_f)
	{
		ft_token_lstclear(&data.tokens);  // А: Чистим выделенную память,
		// data.envp_f = 1; //проверяю как перезаписывается наш envp из односвязного списка t_llist //del
		if (data.envp_f)
			ft_array_envp(&data); //переписываю наш envp, если это нужно
		ft_readline(&data);
		if (!data.free_me.str) //обработка сигнала "control + d"
			break ;



		// char *str = "cat          >	$9 $	$USER;	   '\"file	$ $USER1; $USER2  \"'ffff user  | $USER3 cat< file"; просто тестовая строка
		// if (!ft_strncmp(data.free_me.str, "\n", 1))
		// 	continue ;
		// lexer
		if (ft_get_tokens(data.free_me.str, &data))
			continue ;
		ft_expand(&data);
		ft_symsplit(&data);
		// ft_set_tokens_type(&data);
		data.token_head = data.tokens;
		printf("\n------------------\n");
		while (data.token_head)  // УТЕЧКИ на $PWD... тут - это не страшно, этот принт нужен просто для наглядности в процессе разработки
		{
			printf("string = %s\n", data.token_head->str_val);
			// printf("type == %d\n\n", data.token_head->type);
			data.token_head = data.token_head->next;
		}
		printf("------------------\n");
		// ft_parser(&data);
		// if (ft_executor(&data))
		// 	printf("im found mistake in executor\n"); //del
	}
	ft_token_lstclear(&data.tokens);
	ft_clean_struct(&data);
	return (0);
}

// 1. инициализация структур 
// 2. цикл (1)
// 	2.1 ридлайн
// 	2.2 лексер
// 	2.3 парсер
// 	2.4 экзекве
// 3. деструктор