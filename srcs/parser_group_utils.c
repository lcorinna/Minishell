/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_group_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/26 23:00:53 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_group	*ft_group_lstnew(void)
{
	t_group	*new;

	new = malloc(sizeof(t_group));
	if (NULL == new)
	{
		exit(ENOMEM);
	}
	new->logical_operation = 0;
	new->priority = 0;
	new->nesting_level = 0;
	new->cmds_head = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_group	*ft_group_lstlast(t_group *head)
{
	if (head != NULL)
	{
		while (head->right != NULL)
		{
			head = head->right;
		}
	}
	return (head);
}

void	ft_group_lstadd_front(t_group **head, t_group *new)
{
	if (NULL != new)
	{
		new->left = NULL;
		new->right = *head;
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
			lst_last->right = new;
			new->left = lst_last;
			new->right = NULL;
		}
	}
}

void	ft_group_lstclear(t_group **head)
{
	t_group	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = tmp->right;
		ft_cmd_lstclear(&tmp->cmds_head);
		free(tmp);
	}
}
