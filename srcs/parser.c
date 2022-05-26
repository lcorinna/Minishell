/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/26 18:00:01 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_parn_l(t_info *data)
{
	if (data->token_head->prev && data->token_head->prev->type != PIPE \
		&& data->token_head->prev->type != IF_AND \
		&& data->token_head->prev->type != IF_OR)
		return (ft_perror_token(data, data->token_head->next->str_val));
	else
	{
		data->priority += 1;
		data->token_head = data->token_head->next;
	}
	return (0);
}

static int	ft_check_parn_r(t_info *data)
{
	if (data->token_head->next && data->token_head->next->type != PIPE \
		&& data->token_head->next->type != IF_AND \
		&& data->token_head->next->type != IF_OR)
		return (ft_perror_token(data, data->token_head->next->str_val));
	else
	{
		data->priority -= 1;
		data->token_head = data->token_head->next;
	}
	return (0);
}

static int	ft_fill_cmd(t_info *data)
{
	int	count;

	count = 0;
	while (data->token_head && !ft_strchr(LOGIC_OPER, data->token_head->str_val[0]))
	{
		if (data->token_head->type == PARN_L)
		{
			if (ft_check_parn_l(data))
				return (data->status);
		}
		if (data->token_head->type == PARN_R)
		{
			if (ft_check_parn_r(data))
				return (data->status);
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
		if (data->token_head && ft_check_cmd_str(data))
			return (data->status);
	}
	return (0);
}

static int	ft_get_groups_cmds(t_info *data)
{
	while (data->token_head && data->token_head->type != IF_AND \
			&& data->token_head->type != IF_OR)
	{
		ft_cmd_lstadd_back(&data->group_ptr->cmds_head, ft_cmd_lstnew());
		data->cmds_head = ft_cmd_lstlast(data->group_ptr->cmds_head);
		if (!data->cmds_head || ft_fill_cmd(data))
			return (data->status);
		if (data->token_head && data->token_head->type == PIPE)
			data->token_head = data->token_head->next;
		data->cmds_head->cmd_argv = ft_split(data->cmds_head->cmd_str, ' ');
	}
	return (0);
}

int	ft_get_logic_group(t_info *data)
{
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_group_lstadd_back(&data->group_head, ft_group_lstnew());
		data->group_ptr = ft_group_lstlast(data->group_head);
		if ((data->token_head->type == IF_AND \
			|| data->token_head->type == IF_OR))
		{
			data->group_ptr->logical_operation = data->token_head->type;
			data->group_ptr->priority = data->priority;
			data->token_head = data->token_head->next;
			continue ;
		}
		if (ft_get_groups_cmds(data))
			return (data->status);
	}
	return (0);
}
