/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 13:00:17 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/21 16:35:20 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_llist	*ft_lstnew(void **key, void **value)
{
	t_llist	*new;
	int		lvl;

	new = malloc(sizeof(t_llist));
	if (new == NULL)
		return (NULL);
	if ((ft_memcmp_l("SHLVL", (*key), 6) == 6))
	{
		lvl = ft_atoi((*value));
		lvl++;
		free((*value));
		*value = ft_itoa(lvl);
		if (*value == NULL)
			return (NULL);
	}
	new->value = (*value);
	new->key = (*key);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_front(t_llist **lst, t_llist *new)
{
	if (NULL != new)
	{
		new->next = *lst;
		*lst = new;
	}
}

t_llist	*ft_lstlast(t_llist *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

void	ft_lstadd_back(t_llist **lst, t_llist *new)
{
	t_llist	*lst_last;

	if (new != NULL)
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
