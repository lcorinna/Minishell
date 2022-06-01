/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 22:51:34 by merlich           #+#    #+#             */
/*   Updated: 2022/06/01 18:18:51 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_lstdelone(t_token *lst)
{
	if (NULL != lst)
	{
		free(lst->str_val);
		free(lst);
	}
}

void	ft_token_lstclear(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		ft_token_lstdelone(tmp);
	}
}

void	ft_token_lstadd_prev(t_token *head, t_token *new)
{
	t_token	*tmp;

	tmp = NULL;
	if (head)
	{
		tmp = (head)->prev;
		if (NULL != new)
		{
			if (tmp)
				tmp->next = new;
			new->prev = tmp;
			new->next = head;
			(head)->prev = new;
		}
	}	
}

void	ft_token_lstadd_next(t_token *head, t_token *new)
{
	t_token	*tmp;

	tmp = NULL;
	if (head)
	{
		tmp = (head)->next;
		if (NULL != new)
		{
			(head)->next = new;
			new->prev = head;
			new->next = tmp;
			if (tmp)
				tmp->prev = new;
		}
	}
}

void	ft_token_lstmerge_next(t_token *node)
{
	char	*old_str_val;
	t_token	*tmp;

	old_str_val = NULL;
	if (node != NULL)
	{
		tmp = node->next->next;
		old_str_val = node->str_val;
		node->str_val = ft_strjoin(node->str_val, node->next->str_val);
		free(old_str_val);
		ft_token_lstdelone(node->next);
		node->next = tmp;
		if (tmp != NULL)
			tmp->prev = node;
	}
}
