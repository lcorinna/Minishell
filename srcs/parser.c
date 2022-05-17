/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/17 17:50:50 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_fill_cmd(t_info *data, int priority)
{
	int	count;

	count = 0;
	while (data->token_head && !ft_strchr(LOGIC_OPER, data->token_head->str_val[0]))
	{
		if (data->token_head->type == PARN_L)
		{
			priority++;
			data->token_head = data->token_head->next;
		}
		else if (data->token_head->type == PARN_R)
		{
			priority--;
			data->token_head = data->token_head->next;
		}
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

static int	ft_get_groups_cmds(t_info *data, int priority)
{
	while (data->token_head && data->token_head->type != IF_AND \
			&& data->token_head->type != IF_OR)
	{
		ft_cmd_lstadd_back(&data->group_ptr->cmds_head, ft_cmd_lstnew());
		data->cmds_head = ft_cmd_lstlast(data->group_ptr->cmds_head);
		if (!data->cmds_head || ft_fill_cmd(data, priority))
			return (data->status);
		if (data->token_head && data->token_head->type == PIPE)
			data->token_head = data->token_head->next;
	}
	return (0);
}

int	ft_get_cmds(t_info *data)
{
	static int	priority = 0;

	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_group_lstadd_back(&data->group_head, ft_group_lstnew());
		data->group_ptr = ft_group_lstlast(data->group_head);
		if (ft_get_groups_cmds(data, priority))
			return (data->status);
		if (data->token_head && (data->token_head->type == IF_AND \
			|| data->token_head->type == IF_OR))
		{
			data->group_ptr->logical_operation = data->token_head->type;
			data->group_ptr->priority = priority;
			data->token_head = data->token_head->next;
		}
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
