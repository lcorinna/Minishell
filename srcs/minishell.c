/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/21 23:46:23 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_fill_builtins(t_info *data)
{
	data->res_words[0] = "echo";
	data->res_words[1] = "cd";
	data->res_words[2] = "pwd";
	data->res_words[3] = "export";
	data->res_words[4] = "unset";
	data->res_words[5] = "env";
	data->res_words[6] = "exit";
}

static int	ft_check_parentheses(t_info *data)
{
	int	left;
	int	right;
	int	res;

	left = 0;
	right = 0;
	res = 0;
	data->token_head = data->tokens;
	while (data->token_head)
	{
		if (data->token_head->type == PARN_L)
			left++;
		else if (data->token_head->type == PARN_R)
			right++;
		data->token_head = data->token_head->next;
	}
	if (left == right)
		res = 0;
	else if (left < right)
		res = ft_perror_token(data, ")");
	else if (left > right)
		res = 1;
	return (res);
}

int	ft_lexer(t_info *data)
{
	int	parn_num;
	int	last_type;

	parn_num = 0;
	last_type = UNDEFINED;
	if (ft_get_tokens(data->str, data))
		return (data->status);
	ft_expand(data);
	ft_symsplit(data);
	ft_set_tokens_type(data);
	if (data->tokens && ft_strchr(NOT_FIRST, data->tokens->str_val[0]))
		return (ft_perror_token(data, data->tokens->str_val));
	parn_num = ft_check_parentheses(data);
	if (parn_num == TOKEN_ERROR)
		return (data->status);
	if (data->tokens)
		last_type = ft_token_lstlast(data->tokens)->type;
	if (parn_num || (data->tokens && (last_type == PIPE || last_type == AND \
		|| last_type == IF_AND || last_type == IF_OR)))
	{
		ft_readline(data, "> ", 0);
		if (!data->str)
			return (ft_perror_eof(data));
		if (ft_lexer(data))
			return (data->status);
	}
	return (0);
}

void	ft_cleanup(t_info *data)
{
	data->priority = 0;
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
	ft_token_lstclear(&data->tokens);
	ft_group_lstclear(&data->group_head);
	unlink(HEREDOC);
}

int	main(int argc, char **argv, char **envp)
{
	t_info				data;

	data = (t_info){};
	ft_fill_builtins(&data);
	ft_transfer(argc, argv, envp, &data);
	// ft_signal(); //буду делать в конце
	while (!data.exit_f)
	{
		ft_cleanup(&data);
		// data.envp_f = 1; //проверяю как перезаписывается наш envp из односвязного списка t_llist //del
		if (data.envp_f)
			ft_array_envp(&data); //переписываю наш envp, если это нужно
		ft_readline(&data, SHELL, 1);
		if (!data.str) //обработка сигнала "control + d"
			break ;
		// lexer
		if (ft_lexer(&data))
			continue ;
		ft_check_lexer(&data);
		// parser
		if (ft_get_cmds(&data))
			continue ;
		data.root = ft_group_logic_last(ft_group_lstlast(data.group_head));
		ft_build_bin_tree(&data, ft_group_lstlast(data.group_head));
		ft_in_order_traverse(data.root);
		// ft_checker(&data);
		// executor
		// if (ft_executor(&data))
		// 	printf("im found mistake in executor\n"); //del
	}
	ft_cleanup(&data);
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