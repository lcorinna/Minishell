/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:34:08 by merlich           #+#    #+#             */
/*   Updated: 2022/05/13 00:06:44 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_error(t_info *data, char *infile)
{
	printf("%s\b\b: %s: No such file or directory\n", SHELL, infile);
	// Permission denied // Лучше вернуть perror();
	data->status = errno;
	exit(1); // Отправляем сигнал в main о переходе на новый виток цикла while
}

void	ft_check_redir_in(t_info *data)
{
	char	*infile;

	infile = NULL;
	if (data->token_head->type == REDIR_IN)
	{
		data->token_head = data->token_head->next;
		if (!data->token_head)
		{
			printf("%s\b\b: syntax error near unexpected token `newline'\n", SHELL);
			data->status = 258;
			exit(258);  // Отправляем сигнал в main о переходе на новый виток цикла while
		}
		else
		{
			infile = data->token_head->str_val;
			data->group_head->cmds_head->infile = open(infile, O_RDONLY);  // Нужно получать абсолютный адрес файла (или относительный)
			printf("%d\n", data->group_head->cmds_head->infile);
			if (data->group_head->cmds_head->infile < 0)
				ft_print_error(data, infile);
		}
	}
}