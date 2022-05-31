/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/31 19:13:24 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_error_message_unset(t_info *data, char *str)
{
	ft_print_shell(NULL, SHELL);
	ft_putstr_fd(": unset: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	data->status = 1;
}

void	ft_check_arguments_unset(t_info *data, char **arr)
{
	int	i[2];

	i[0] = 1;
	while (arr[i[0]])
	{
		i[1] = 0;
		while (arr[i[0]][i[1]])
		{
			if (i[1] == 0 && arr[i[0]][i[1]] >= '0' && arr[i[0]][i[1]] <= '9')
			{
				ft_error_message_unset(data, arr[i[0]]);
				break ;
			}
			if ((arr[i[0]][i[1]] >= '!' && arr[i[0]][i[1]] <= '/') || \
				(arr[i[0]][i[1]] >= ':' && arr[i[0]][i[1]] <= '@') || \
				(arr[i[0]][i[1]] >= '[' && arr[i[0]][i[1]] <= '^') || \
				(arr[i[0]][i[1]] >= '{' && arr[i[0]][i[1]] <= '~'))
			{
				ft_error_message_unset(data, arr[i[0]]);
				break ;
			}
			i[1]++;
		}
		i[0]++;
	}
}

void	ft_delete_argument(t_llist *del, t_llist *envp_l, int num)
{
	t_llist	*tmp;

	tmp = envp_l;
	num--;
	while (num != 0)
	{
		tmp = tmp->next;
		num--;
	}
	tmp->next = tmp->next->next;
	if (del)
	{
		free(del->key);
		free(del->value);
		free(del);
	}
}

void	ft_find_argument(t_llist *envp_l, char **arr)
{
	t_llist	*tmp;
	int		len;
	int		i;
	int		num;

	i = 1;
	while (arr[i])
	{
		num = 0;
		tmp = envp_l;
		len = ft_strlen(arr[i]);
		while (tmp)
		{
			if (ft_memcmp_l(arr[i], tmp->key, len) == len)
			{
				ft_delete_argument(tmp, envp_l, num);
				break ;
			}
			tmp = tmp->next;
			num++;
		}
		i++;
	}
}

void	ft_unset(t_info *data, t_llist *envp_l, char **arr)
{
	ft_check_arguments_unset(data, arr);
	ft_find_argument(envp_l, arr);
	data->envp_f = 1;
}
