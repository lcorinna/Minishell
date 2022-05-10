/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_group_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/10 23:01:36 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_group	*ft_group_lstnew(void)
{
	t_group	*new;

	new = malloc(sizeof(t_group));
	if (NULL == new)
	{
		return (NULL);  // Отправить сигнал, в основной цикл while о переходе
	}					// на следующую итерацию (continue) с очисткой памяти
	new->cmds_head = NULL;  // выделенной на текущей итерации
	new->next = NULL;
	return (new);
}

t_group	*ft_group_lstlast(t_group *head)
{
	if (head != NULL)
	{
		while (head->next != NULL)
		{
			head = head->next;
		}
	}
	return (head);
}

void	ft_group_lstadd_front(t_group **head, t_group *new)
{
	if (NULL != new)
	{
		new->next = *head;
		*head = new;
	}
}

void	ft_group_lstadd_back(t_group **head, t_group *new)
{
	t_group	*lst_last;

	if (NULL != new)
	{
		lst_last = ft_group_lstlast(*head);
		if (lst_last == NULL)
		{
			ft_group_lstadd_front(head, new);
		}
		else
		{
			lst_last->next = new;
			new->next = NULL;
		}
	}
}

void	ft_group_lstclear(t_group **head)
{
	t_group	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		ft_cmd_lstclear(&tmp->cmds_head);
		free(tmp);
	}
}
