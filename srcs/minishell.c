/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/14 23:22:00 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int	ft_lexer(t_info *data)
{
	int	last_type;

	last_type = UNDEFINED;
	if (ft_get_tokens(data->free_me.str, data))
		return (LEXER_ERROR);
	ft_expand(data);
	ft_symsplit(data);
	ft_set_tokens_type(data);
	if (data->tokens && (data->tokens->type == PIPE || data->tokens->type == AND \
		|| data->tokens->type == IF_AND || data->tokens->type == IF_OR))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", data->tokens->str_val);
		return (LEXER_ERROR);
	}
	if (data->tokens)
		last_type = ft_token_lstlast(data->tokens)->type;
	if (data->tokens && (last_type == PIPE || last_type == AND \
		|| last_type == IF_AND || last_type == IF_OR))
	{
		ft_readline(data, "> ", 0);
		if (!data->free_me.str) //обработка сигнала "control + d"
		{
			printf("\x1b[F> %s\b\b: syntax error: unexpected end of file\n", SHELL);
			return (LEXER_ERROR);
		}
		if (ft_lexer(data))
			return (LEXER_ERROR);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info				data;

	data = (t_info){};
	ft_transfer(argc, argv, envp, &data);
	// ft_signal(); //буду делать в конце
	while (!data.exit_f)
	{
		free(data.path);
		data.path = NULL;
		ft_token_lstclear(&data.tokens);  	// А: Чистим выделенную память
		ft_group_lstclear(&data.group_head);  // Очистка t_group
		unlink(HEREDOC);
		// data.envp_f = 1; //проверяю как перезаписывается наш envp из односвязного списка t_llist //del
		if (data.envp_f)
			ft_array_envp(&data); //переписываю наш envp, если это нужно
		ft_readline(&data, SHELL, 1);
		if (!data.free_me.str) //обработка сигнала "control + d"
			break ;
		// lexer
		if (ft_lexer(&data))
			continue ;
		data.token_head = data.tokens;
		printf("------------------\n");
		while (data.token_head)
		{
			printf("string = %s\n", data.token_head->str_val);
			// printf("type == %d\n\n", data.token_head->type);
			data.token_head = data.token_head->next;
		}
		printf("------------------\n");
		// parser
		if (ft_get_cmds(&data))
			continue ;
		// executor
		// if (ft_executor(&data))
		// 	printf("im found mistake in executor\n"); //del
	}
	ft_token_lstclear(&data.tokens);
	ft_group_lstclear(&data.group_head);
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