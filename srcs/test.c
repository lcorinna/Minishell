/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/28 23:50:40 by merlich          ###   ########.fr       */
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
		if (data.envp_f)
			ft_array_envp(&data); //переписываю наш envp, если это нужно
		ft_readline(&data);
		if (!data.free_me.str) //обработка сигнала "control + d"
			break ;

	

		// char *str = "cat          >	$9 $	$USER;	   '\"file	$ $USER1; $USER2  \"'ffff user  | $USER3 cat< file"; просто тестовая строка
		
		// lexer
		if (ft_get_tokens(data.free_me.str, &data))
			continue ;
		ft_expand(&data);
		// ft_set_tokens_type(&data);
		data.token_head = data.tokens;
		while (data.token_head)
		{
			printf("string = %s\n", data.token_head->str_val);
			// printf("type == %d\n\n", head->type);
			data.token_head = data.token_head->next;
		}
		ft_token_lstclear(&data.tokens);
		data.tokens = NULL;
		// parser
		// executor
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