/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/27 13:40:58 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_printing_machine(t_llist *tmp)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp->key, 1);
	if (tmp->value != NULL)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(tmp->value, 1);
		ft_putstr_fd("\"\n", 1);
	}
	else if (tmp->value == NULL)
		ft_putstr_fd("\n", 1);
}

void	ft_print_exp(t_llist *export)
{
	t_llist	*tmp;
	int		quantity;
	int		i;

	tmp = export;
	quantity = 0;
	i = 1;
	while (tmp && ++quantity != -1)
		tmp = tmp->next;
	while (quantity >= i)
	{
		tmp = export;
		while (tmp)
		{
			// printf("%d - %s\n", tmp->num, tmp->key); //del
			if (i == tmp->num)
				ft_printing_machine(tmp);
			tmp = tmp->next;
		}
		i++;
	}
}

void	ft_make_zero_num(t_llist *export)
{
	t_llist	*tmp;

	tmp = export;
	while (tmp)
	{
		tmp->num = 0;
		tmp = tmp->next;
	}
}

void	ft_sort_export(t_llist *export)
{
	int		number;
	char	*max;
	t_llist	*tmp;

	number = 0;
	tmp = export;
	while (tmp && ++number != -1) //считаю сколько всего элементов
	{
		// printf("%d - %s\n", number, tmp->key); //del
		tmp = tmp->next;
	}
	// printf("num - %d\n", number); //del
	while (number != 0)
	{
		tmp = export;
		max = ft_max_key(export);
		// printf("\n%d - %s\n", number, max); //del
		while (tmp)
		{
			if (tmp->num == 0 && ft_strncmp(max, tmp->key, ft_strlen(tmp->key)) == 0)
			{
				tmp->num = number;
				break ;
			}
			tmp = tmp->next;
		}
		number--;
	}
}

void	ft_need_sort(t_llist *export)
{
	t_llist	*tmp;
	int		need_sort;

	tmp = export;
	need_sort = 0;
	while (tmp)
	{
		if (tmp->num == 0)
			need_sort = 1;
		tmp = tmp->next;
	}
	if (need_sort == 1)
	{
		ft_make_zero_num(export);
		ft_sort_export(export);
	}
}
