/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:28:43 by merlich           #+#    #+#             */
/*   Updated: 2022/05/28 19:57:04 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = NULL;
	if (content != NULL)
	{
		new = malloc(sizeof(t_list));
		if (NULL == new)
		{
			exit(ENOMEM);
		}
		new->content = content;
		new->next = NULL;
	}
	return (new);
}
