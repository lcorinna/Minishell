/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:34:08 by merlich           #+#    #+#             */
/*   Updated: 2022/05/13 22:31:29 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_print_error(t_info *data, char *outfile)
{
	printf("%s\b\b: %s: Permission denied\n", SHELL, outfile);  // Think about it
	data->status = errno;
	exit(1); // Отправляем сигнал в main о переходе на новый виток цикла while
}

void	ft_check_redir_out(t_info *data)
{
	char	*outfile;

	outfile = NULL;
	if (data->token_head->type == REDIR_OUT)
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
			outfile = data->token_head->str_val;
			data->group_head->cmds_head->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 000777);
			printf("%d\n", data->group_head->cmds_head->outfile);
			if (data->group_head->cmds_head->outfile < 0)
				ft_print_error(data, outfile);
		}
	}
}
