/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:51:34 by merlich           #+#    #+#             */
/*   Updated: 2022/04/19 22:51:57 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(tmp->str_val);
		free(tmp);
	}
}
