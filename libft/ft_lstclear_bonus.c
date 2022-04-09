/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:42:21 by merlich           #+#    #+#             */
/*   Updated: 2021/10/26 19:30:10 by merlich          ###   ########.fr       */
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
