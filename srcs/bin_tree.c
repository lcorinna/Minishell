/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:09:34 by merlich           #+#    #+#             */
/*   Updated: 2022/05/25 23:09:48 by merlich          ###   ########.fr       */
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

void	ft_build_bin_tree(t_info *data, t_group *last)
{
	t_group	*log_last;
	t_group	*log_penult;

	log_last = ft_group_logic_last(last);
	if (log_last)
	{
		log_last->left->right = NULL;
		log_last->right->left = NULL;
		log_penult = ft_group_logic_last(ft_group_logic_last(log_last->left));
		if (log_penult)
			log_last->left = log_penult;
		if (log_penult && log_penult->logical_operation)
			ft_build_bin_tree(data, log_penult);
	}
}

void	ft_free_bin_tree(t_group **root)
{
	if (*root)
	{
		ft_free_bin_tree((*root)->left);
		ft_cmd_lstclear(&(*root)->cmds_head);
		free((*root));
		ft_free_bin_tree((*root)->right);
	}
}
