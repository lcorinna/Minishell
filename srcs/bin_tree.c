/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:09:34 by merlich           #+#    #+#             */
/*   Updated: 2022/05/27 20:39:16 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_build_left_branch(t_group **root)
{
	t_group	*tmp;
	t_group	*min_left;
	
	tmp = (*root)->left;
	min_left = ft_get_logic_min_left((*root)->left);
	if (min_left)
		(*root)->left = min_left;
	tmp->right = NULL;
}

static void	ft_build_right_branch(t_group **root)
{
	t_group	*tmp;
	t_group	*min_right;

	tmp = (*root)->right;
	min_right = ft_get_logic_min_right((*root)->right);
	if (min_right)
		(*root)->left = min_right;
	tmp->left = NULL;
}

void	ft_build_bin_tree(t_group **root)
{
	if (*root)
	{
		ft_build_left_branch(root);
		printf("root.left = %d\n", (*root)->left->logical_operation);
		ft_build_bin_tree(&(*root)->left);
		// ft_build_right_branch(root);
		// ft_build_bin_tree(&(*root)->right);
	}
}

static void	ft_free_node(t_group **root)
{
	t_group	*tmp;
	
	tmp = *root;
	ft_cmd_lstclear(&tmp->cmds_head);
	free(tmp);
}

void	ft_free_bin_tree(t_group **root)
{
	if ((*root))
	{
		ft_free_bin_tree(&(*root)->left);
		ft_free_bin_tree(&(*root)->right);
		ft_free_node(root);
		*root = NULL;
	}
}
