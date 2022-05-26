/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/26 19:25:59 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(char *s1, char *s2) //utils
{
	int					res;
	int					len;
	int					i;

	res = 0;
	i = 0;
	len = (int)ft_strlen(s1);
	if (len > (int)ft_strlen(s2))
		len = (int)ft_strlen(s2);
	while ((i != len) && ((s1[i] != '\0') || (s2[i] != '\0')))
	{
		if (s1[i] != s2[i])
		{
			res = s1[i] - s2[i];
			break ;
		}
		i++;
	}
	return (res);
}

void	ft_cp_env_in_exp(t_info *data, t_llist *envp_l)
{
	t_llist	*tmp;
	t_llist	*new;
	char	*key1;
	char	*value1;

	tmp = envp_l;
	while (tmp)
	{
		key1 = ft_strdup(tmp->key);
		value1 = ft_strdup(tmp->value);
		if (key1 == NULL || value1 == NULL)
			ft_perror_exit_child("", 12);
		new = ft_lstnew(key1, value1);
		if (new == NULL)
			ft_perror_exit_child("", 12);
		ft_lstadd_back(&data->export, new);
		// printf("key - %s\n", tmp->key); //del
		tmp = tmp->next;
	}
}

char	*ft_max_key(t_llist *export)
{
	t_llist	*tmp;
	char	*res;
	char	*min;

	min = ft_strdup("                                         ");
	if (min == NULL)
		ft_perror_exit_child("", 12);
	tmp = export;
	res = min;
	while (tmp)
	{
		// if (tmp->num == 0 && (ft_strcmp(res, tmp->key) < 0))
		// printf("\ntmp->key - %s\n", tmp->key); //del
		// printf("tmp->num - %d\n", tmp->num); //del
		if (tmp->num == 0 && (ft_strncmp(res, tmp->key, ft_strlen(res)) < 0))
			res = tmp->key;
		tmp = tmp->next;
	}
	free(min);
	// sleep(22); //del
	return (res);
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

void	ft_printing_machine(t_llist *tmp)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp->key, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(tmp->value, 1);
	ft_putstr_fd("\"\n", 1);
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

void	ft_print_sort(t_info *data)
{
	if (data->export == NULL)
		ft_cp_env_in_exp(data, data->envp_list);
	ft_need_sort(data->export);
	ft_print_exp(data->export);
}

void	ft_export(t_info *data, t_llist *envp_l, char **arr)
{
	if (arr[0] != NULL || arr[1] == NULL)
		ft_print_sort(data);
}
