/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:09:34 by merlich           #+#    #+#             */
/*   Updated: 2022/05/19 23:44:48 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_group	*ft_group_logic_last(t_group *last)
{

	while (last && !last->logical_operation)
	{
		last = last->left;
	}
	return (last);
}

void	ft_build_bin_tree(t_info *data)
{
	t_group	*tmp;
	t_group	*last;
	t_group	*last_but_one;

	last = ft_group_logic_last(ft_group_lstlast(data->group_head));
	last_but_one = ft_group_logic_last(ft_group_lstlast(last->left));
	tmp = last->left;
	last->left = last_but_one;
	tmp->right = NULL;
}
