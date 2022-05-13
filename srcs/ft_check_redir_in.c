/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:34:08 by merlich           #+#    #+#             */
/*   Updated: 2022/05/14 00:03:52 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	ft_print_error(t_info *data, char *infile)
// {
// 	printf("%s\b\b: %s: No such file or directory\n", SHELL, infile);
// 	// Permission denied // Лучше вернуть perror();
// 	data->status = errno;
// }

// static void	ft_print_error(t_info *data, char *infile)
// {
// 	char	*s1;
// 	char	*s2;

// 	s1 = ft_strjoin(SHELL, "\b\b: ");
// 	s2 = ft_strjoin(s1, infile);
// 	perror(s2);
// 	free(s1);
// 	free(s2);
// 	data->status = errno;
// }

int	ft_check_redir_in(t_info *data)
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
			return (data->status);
		}
		else
		{
			infile = data->token_head->str_val;
			data->group_head->cmds_head->infile = open(infile, O_RDONLY);
			if (data->group_head->cmds_head->infile < 0)
			{
				ft_print_error(data, infile);
				return (data->status);
			}
		}
	}
	return (0);
}