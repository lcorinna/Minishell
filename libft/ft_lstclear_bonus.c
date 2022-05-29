/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:42:21 by merlich           #+#    #+#             */
/*   Updated: 2022/05/28 20:02:01 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next1;

	if (NULL != del)
	{
		while (*lst)
		{
			next1 = *lst;
			*lst = (*lst)->next;
			ft_lstdelone(next1, del);
		}
	}
}
