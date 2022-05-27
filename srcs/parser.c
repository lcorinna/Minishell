/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/27 23:24:26 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_parn_l(t_info *data)
{
	if (data->token_head->prev && data->token_head->prev->type != PIPE \
		&& data->token_head->prev->type != IF_AND \
		&& data->token_head->prev->type != IF_OR \
		&& data->token_head->prev->type != PARN_L)
		return (ft_perror_token(data, data->token_head->next->str_val));
	if (!data->token_head->prev \
		|| data->token_head->prev->type == IF_AND \
		|| data->token_head->prev->type == IF_OR \
		|| data->token_head->prev->type == PARN_L)
	{
		// data->priority_step += 1;
		data->nesting_level++;
	}
	data->token_head = data->token_head->next;
	return (0);
}

static int	ft_check_parn_r(t_info *data)
{
	if (data->token_head->next && data->token_head->next->type != PIPE \
		&& data->token_head->next->type != IF_AND \
		&& data->token_head->next->type != IF_OR \
		&& data->token_head->next->type != PARN_R)
		return (ft_perror_token(data, data->token_head->next->str_val));
	if (!data->token_head->next \
		|| data->token_head->next->type == IF_AND \
		|| data->token_head->next->type == IF_OR \
		|| data->token_head->next->type == PARN_R)
	{
		// data->priority_step -= 1;
		data->nesting_level--;
	}
	data->token_head = data->token_head->next;
	return (0);
}

static int	ft_fill_cmd(t_info *data)
{
	int	count;

	count = 0;
	while (data->token_head && !ft_strchr(LOGIC, data->token_head->str_val[0]))
	{
		if (data->token_head->type == PARN_L && ft_check_parn_l(data))
			return (data->status);
		if (data->token_head->type == PARN_R && ft_check_parn_r(data))
			return (data->status);
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
	// data->priority += data->priority_step;
	return (0);
}

int	ft_get_logic_group(t_info *data)
{
	data->token_head = data->tokens;
	while (data->token_head)
	{
		ft_group_lstadd_back(&data->group_head, ft_group_lstnew());
		data->group_ptr = ft_group_lstlast(data->group_head);
		// data->group_ptr->priority = data->priority;
		if ((data->token_head->type == IF_AND \
			|| data->token_head->type == IF_OR))
		{
			data->group_ptr->logical_operation = data->token_head->type;
			// data->group_ptr->priority = data->priority;
			// data->priority++;
			data->group_ptr->nesting_level = data->nesting_level;
			data->token_head = data->token_head->next;
			continue ;
		}
		if (ft_get_groups_cmds(data))
			return (data->status);
		data->group_ptr->nesting_level = -1;
	}
	return (0);
}
