/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/15 22:48:44 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


static int	ft_fill_cmd(t_info *data)
{
	int	count;

	count = 0;
	while (data->token_head && data->token_head->type != PIPE)
	{
		if (data->token_head && ft_check_redir_insource(data))
			return (data->status);
		if (data->token_head && ft_check_redir_in(data))
			return (data->status);
		if (data->token_head && ft_check_redir_out(data))
			return (data->status);
		if (data->token_head && ft_check_redir_append(data))
			return (data->status);
		if (count == 0)
		{
			if (data->token_head && ft_check_cmd_path(data))
				return (data->status);
			count++;
		}
		else
		{
			if (data->token_head && ft_check_cmd_argv(data))
				return (data->status);
			count++;
		}
	}
	return (0);
}

int	ft_get_cmds(t_info *data)
{
	ft_group_lstadd_back(&data->group_head, ft_group_lstnew());  // Если уже разбили на логические группы, закомментировать/удалить
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_cmd_lstadd_back(&data->group_head->cmds_head, ft_cmd_lstnew());
		data->cmds_head = ft_cmd_lstlast(data->group_head->cmds_head);
		if (!data->cmds_head || ft_fill_cmd(data))
			return (data->status);
		if (data->token_head && data->token_head->type == PIPE)
			data->token_head = data->token_head->next;
	}
	return (0);
} 


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
