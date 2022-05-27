/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:36:32 by merlich           #+#    #+#             */
/*   Updated: 2022/05/27 22:46:17 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_get_max_level(t_group *group_head)
{
	int	max;

	max = 0;
	while (group_head)
	{
		if (group_head->logical_operation && group_head->nesting_level > max)
			max = group_head->nesting_level;
		group_head = group_head->right;
	}
	return (max);
}

static int	ft_get_min_level(t_group *group_head)
{
	int	min;

	min = ft_get_max_level(group_head);
	while (group_head)
	{
		if (group_head->logical_operation && group_head->nesting_level < min)
			min = group_head->nesting_level;
		group_head = group_head->right;
	}
	return (min);
}

t_group	*ft_get_logic_min_last(t_group *group_head)
{
	int		min;
	t_group	*last;

	min = ft_get_min_level(group_head);
	last = ft_group_lstlast(group_head);
	while (last && last->left && !(last->logical_operation \
			&& last->nesting_level == min))
		last = last->left;
	return (last);
}
