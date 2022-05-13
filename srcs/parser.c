/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/13 12:06:55 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
static void	ft_fill_cmd(t_info *data)
{
	// t_cmds	*cmd_head;

	// cmd_head = data->group_head->cmds_head;
	while (data->token_head && data->token_head->type != PIPE)
	{
		ft_check_redir_insource(data);
		ft_check_redir_in(data);
		ft_check_redir_out(data);
		
		// else if (data->token_head->type == REDIR_APPEND)
		// {
		// 	data->token_head->next->str_val  // outfile (We have to check access/create if doesn t exist)
		// 	data->token_head = data->token_head->next;
		// }
		// else if (data->token_head->type == WORD we don t have cmd)
		// 	// set cmd (Check access(cmd, X))
		// else if (data->token_head->type == WORD we already have cmd) // It can be flags '-' or args of cmd
		// 	// (error msg and return () + signal to continue main while loop)
		data->token_head = data->token_head->next;
	}
}

void	ft_get_cmds(t_info *data)
{
	// t_cmds	**cmds_head;

	ft_group_lstadd_back(&data->group_head, ft_group_lstnew());  // Если уже разбили на логические группы, закомментировать/удалить
	// cmds_head = &data->group_head->cmds_head;
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_cmd_lstadd_back(&data->group_head->cmds_head, ft_cmd_lstnew());
		ft_fill_cmd(data);
		if (data->token_head && data->token_head->type == PIPE)
			data->token_head = data->token_head->next;
	}
} 
*/

// int	main(void)
// {
// 	t_info	data;

// 	data = (t_info){};
// 	ft_group_lstadd_back(&data.group_head, ft_group_lstnew());
// 	// ft_cmd_lstadd_back(&data.group_head->cmds_head, ft_cmd_lstnew());
// 	// ft_cmd_lstadd_back(&data.group_head->cmds_head, ft_cmd_lstnew());
// 	// ft_cmd_lstadd_back(&data.group_head->cmds_head, ft_cmd_lstnew());
// 	// ft_cmd_lstadd_back(&data.group_head->cmds_head, ft_cmd_lstnew());
// 	// ft_cmd_lstadd_back(&data.group_head->cmds_head, ft_cmd_lstnew());
// 	// t_cmds	*head = data.group_head->cmds_head;
// 	while (1)
// 	{
// 		ft_get_cmds(&data);
// 		printf("%d\n", data.group_head->cmds_head->infile);
// 		// head = head->next;
// 	}

// 	ft_group_lstclear(&data.group_head);
// 	return (0);
// }
