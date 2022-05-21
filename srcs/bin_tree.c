/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:09:34 by merlich           #+#    #+#             */
/*   Updated: 2022/05/21 22:37:34 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_group	*ft_group_logic_last(t_group *last)
{

	while (last && !last->logical_operation)
	{
		last = last->left;
	}
	return (last);
}

// static t_group	*ft_group_logic_first(t_group *head)
// {

// 	while (head && !head->logical_operation)
// 	{
// 		head = head->right;
// 	}
// 	return (head);
// }

void	ft_build_bin_tree(t_info *data, t_group *last)
{
	t_group	*log_last;
	t_group	*log_last_but_one;

	log_last = ft_group_logic_last(last);
	if (log_last)
	{
		log_last->left->right = NULL;
		log_last->right->left = NULL;
		log_last_but_one = ft_group_logic_last(ft_group_logic_last(log_last->left));
		if (log_last_but_one)
			log_last->left = log_last_but_one;
		if (log_last_but_one && log_last_but_one->logical_operation)
			ft_build_bin_tree(data, log_last_but_one);
	}
}

void	ft_in_order_traverse(t_group *root)
{
	if (root)
	{
		ft_in_order_traverse(root->left);
		if (root->logical_operation == 9)
			printf("&&\n");
		if (root->logical_operation == 10)
			printf("||\n");
		if (root->logical_operation == 0)
		{
			if (root->cmds_head)
				printf("%s\n", root->cmds_head->cmd_path);
		}
		ft_in_order_traverse(root->right);
	}
}
