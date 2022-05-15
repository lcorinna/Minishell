/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 22:09:17 by merlich           #+#    #+#             */
/*   Updated: 2022/05/15 21:40:22 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*ft_cmd_lstnew(void)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (NULL == new)
	{
		exit (-1);  	// Отправить сигнал, в основной цикл while о переходе
	}					// на следующую итерацию (continue) с очисткой памяти
	new->infile = 0; 	 // выделенной на текущей итерации
	new->outfile = 1;
	new->cmd_path = NULL;
	new->cmd_argv = NULL;
	new->next = NULL;
	return (new);
}

t_cmds	*ft_cmd_lstlast(t_cmds *head)
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

void	ft_cmd_lstadd_front(t_cmds **head, t_cmds *new)
{
	if (NULL != new)
	{
		new->next = *head;
		*head = new;
	}
}

void	ft_cmd_lstadd_back(t_cmds **head, t_cmds *new)
{
	t_cmds	*lst_last;

	if (NULL != new)
	{
		lst_last = ft_cmd_lstlast(*head);
		if (lst_last == NULL)
		{
			ft_cmd_lstadd_front(head, new);
		}
		else
		{
			lst_last->next = new;
			new->next = NULL;
		}
	}
}

void	ft_cmd_lstclear(t_cmds **head)
{
	t_cmds	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = tmp->next;
		if (tmp->infile != 0)
		{
			close(tmp->infile);
			tmp->infile = 0;
		}
		if (tmp->outfile != 1)
		{
			close(tmp->outfile);
			tmp->outfile = 1;
		}
		free(tmp->cmd_path);
		free(tmp->cmd_argv);
		free(tmp);
	}
}
