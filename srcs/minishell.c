/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/17 00:06:42 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_perror(t_info *data, char *msg)
// {
// 	char	*s;
// 	char	*s1;
// 	char	*tmp;

// 	tmp = ft_strjoin(SHELL, "\b\b: syntax error near unexpected token ");
// 	s = ft_strjoin_three(tmp, "`", data->tokens->str_val);
// 	free(tmp);
// 	s1 = ft_strjoin(s, "'\n");
// 	free(s);
// 	ft_putstr_fd(s1, 2);
// }

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

static int	ft_lexer(t_info *data)
{
	int	last_type;

	last_type = UNDEFINED;
	if (ft_get_tokens(data->str, data))
		return (LEXER_ERROR);
	ft_expand(data);
	ft_symsplit(data);
	ft_set_tokens_type(data);
	if (data->tokens && (data->tokens->type == PIPE || data->tokens->type == AND \
		|| data->tokens->type == IF_AND || data->tokens->type == IF_OR))
	{
		printf("%s\b\b: syntax error near unexpected token `%s'\n", SHELL, data->tokens->str_val);
		return (LEXER_ERROR);
	}
	if (data->tokens)
		last_type = ft_token_lstlast(data->tokens)->type;
	if (data->tokens && (last_type == PIPE || last_type == AND \
		|| last_type == IF_AND || last_type == IF_OR))
	{
		ft_readline(data, "> ", 0);
		if (!data->str) //обработка сигнала "control + d"
		{
			printf("\x1b[F> %s\b\b: syntax error: unexpected end of file\n", SHELL);
			return (LEXER_ERROR);
		}
		if (ft_lexer(data))
			return (LEXER_ERROR);
	}
	return (0);
}

void	ft_cleanup(t_info *data)
{
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
		ft_checker(&data);
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