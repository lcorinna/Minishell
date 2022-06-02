/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:12:55 by merlich           #+#    #+#             */
/*   Updated: 2022/05/28 19:47:42 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_last;

	if (NULL != new)
	{
		lst_last = ft_lstlast(*lst);
		if (lst_last == NULL)
		{
			ft_lstadd_front(lst, new);
		}
		else
		{
			lst_last->next = new;
		}
	}
}
