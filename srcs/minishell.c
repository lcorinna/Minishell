/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:33:09 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/31 22:57:53 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fill_builtins(t_info *data)
{
	data->res_words[0] = "echo";
	data->res_words[1] = "cd";
	data->res_words[2] = "pwd";
	data->res_words[3] = "export";
	data->res_words[4] = "unset";
	data->res_words[5] = "env";
	data->res_words[6] = "exit";
	data->res_words[7] = "ECHO";
	data->res_words[8] = "CD";
	data->res_words[9] = "PWD";
	data->res_words[10] = "EXPORT";
	data->res_words[11] = "UNSET";
	data->res_words[12] = "ENV";
	data->res_words[13] = "EXIT";
	data->res_words[14] = NULL;
}

void	ft_cleanup(t_info *data)
{
	data->nesting_level = 0;
	ft_token_lstclear(&data->tokens);
	ft_free_bin_tree(&data->root);
	data->group_head = NULL;
	unlink(HEREDOC);
}

static int	ft_lexer(t_info *data)
{
	if (ft_get_tokens_from_string(data))
		return (data->status);
	if (ft_check_tokens(data))
		return (data->status);
	// Обрезать кавычки " '
	ft_cut_all_quotes(data);
	// ft_check_lexer(data);
	return (0);
}

static int	ft_parser(t_info *data)
{
	if (ft_get_logic_group(data))
	{
		ft_group_lstclear(&data->group_head);
		return (data->status);
	}
	// ft_check_parser(data);
	data->root = ft_get_logic_min_last(data->group_head);
	ft_build_bin_tree(&data->root);
	// ft_check_bin_tree(data.root);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info				data;

	data = (t_info){};
	ft_fill_builtins(&data);
	ft_transfer(argc, argv, envp, &data);
	while (!data.exit_f)
	{
		ft_signal(&data, 1);
		ft_cleanup(&data);
		if (data.envp_f) //флаг нужен?
			ft_array_envp(&data); //переписываю envp
		if (!ft_readline(&data, SHELL, 1)) //обработка сигнала "control + d"
			break ;
		// lexer
		if (ft_lexer(&data))
			continue ;
		// parser
		if (ft_parser(&data))
			continue ;
		// // executor
		ft_executor(&data, data.root);
	}
	ft_clean_struct(&data);
	return (0);
}
