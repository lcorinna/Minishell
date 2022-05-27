/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree_branches_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 20:04:49 by merlich           #+#    #+#             */
/*   Updated: 2022/05/27 20:32:50 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_get_max_level(t_group *group_head, t_group **root)
{
	int	max;

	max = 0;
	while (group_head && group_head != *root)
	{
		if (group_head->logical_operation && group_head->nesting_level > max)
			max = group_head->nesting_level;
		group_head = group_head->right;
	}
	return (max);
}

static int	ft_get_min_level(t_group *group_head, t_group **root)
{
	int	min;

	min = ft_get_max_level(group_head, root);
	while (group_head && group_head != *root)
	{
		if (group_head->logical_operation && group_head->nesting_level < min)
			min = group_head->nesting_level;
		group_head = group_head->right;
	}
	return (min);
}

static t_group	*ft_group_lstfirst(t_group *root)
{
	while (root)
	{
		root = root->left;
	}
	return (root);
}

t_group	*ft_get_logic_min_left(t_group *root)
{
	int		min;
	t_group *first;

	first = ft_group_lstfirst(root);
	min = ft_get_min_level(first, &root);
	// root = root->left;
	while (root && !(root->logical_operation && root->nesting_level == min))
	{
		root = root->left;
	}
	return (root);
}

t_group	*ft_get_logic_min_right(t_group *root)
{
	int		min;

	min = ft_get_min_level(root, &root);
	while (root && !(root->logical_operation && root->nesting_level == min))
	{
		root = root->right;
	}
	return (root);
}
