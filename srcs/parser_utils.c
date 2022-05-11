/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:40:27 by merlich           #+#    #+#             */
/*   Updated: 2022/05/12 00:02:08 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_fill_here_doc(t_data *head, char **argv)
// {
// 	int		fd;
// 	char	*buff;

// 	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 000777);
// 	if (head->infile < 0)
// 		ft_error_parent("Error infile", head);
// 	write(1, "pipe here_doc> ", 15);
// 	buff = get_next_line(0);
// 	while (buff && ft_strncmp(buff, argv[2], ft_strlen(argv[2])))
// 	{
// 		write(1, "pipe here_doc> ", 15);
// 		write(fd, buff, ft_strlen(buff));
// 		free(buff);
// 		buff = get_next_line(0);
// 	}
// 	free(buff);
// 	close(fd);
// }

// ft_readline(&data, "minishell$ ", 1);
// 		if (!data.free_me.str) //обработка сигнала "control + d"
// 		{
// 			break ;
// 		}

void	ft_check_redir_insource(t_info *data)
{
	char	*limiter;

	if (data->token_head->type == REDIR_INSOURCE)
	{
		data->token_head = data->token_head->next;
		limiter = data->token_head->str_val;  // LIMITER (We have to create here_doc.tmp)
		
	
	
	}
}