/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:51:34 by merlich           #+#    #+#             */
/*   Updated: 2022/05/03 23:39:38 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_token_last_but_one(t_token *head)
{
	if (head != NULL)
	{
		while (head->next->next != NULL)
		{
			head = head->next;
		}
	}
	return (head);
}

void	ft_token_dellast(t_token **head)
{
	t_token	*last;
	t_token *last_but_one;

	last_but_one = ft_token_last_but_one(*head);
	last = ft_token_lstlast(*head);
	last_but_one->next = NULL;
	free(last);
}

void	ft_token_lstclear(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		if (ft_strncmp(tmp->str_val, " ", ft_strlen(tmp->str_val)))
			free(tmp->str_val);
		free(tmp);
	}
}

void	ft_token_lstadd_prev(t_token **head, t_token *new)
{
	if (NULL != new)
	{
		new->next = *head;
		*head = new;
	}
	*head = (*head)->next;
}

void	ft_token_lstadd_next(t_token **head, t_token *new)
{
	t_token	*lst_next;

	if (NULL != new)
	{
		lst_next = (*head)->next;
		(*head)->next = new;
		new->next = lst_next;
	}
}
