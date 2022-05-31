/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/31 16:32:37 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_sort(t_info *data)
{
	ft_need_sort(data->export);
	ft_print_exp(data->export);
}

int	ft_error_message_export(t_info *data, char *str)
{
	ft_putstr_fd("minishell: export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	data->status = 1;
	return (-1);
}

int	ft_check_arguments_export(t_info *data, char *arr)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (arr[i])
	{
		if (i == 0 && arr[i] >= '0' && arr[i] <= '9')
			return (ft_error_message_export(data, arr));
		if ((arr[i] >= '!' && arr[i] <= '/') || \
				(arr[i] >= ':' && arr[i] <= '<') || \
					(arr[i] >= '>' && arr[i] <= '@') || \
						(arr[i] >= '[' && arr[i] <= '^') || \
							(arr[i] >= '{' && arr[i] <= '~'))
			return (ft_error_message_export(data, arr));
		if (arr[i] == '=')
			res = 2;
		i++;
	}
	return (res);
}

void	ft_export(t_info *data, char **arr)
{
	if (data->export == NULL)
		ft_cp_env_in_exp(data, data->envp_list);
	if (arr[0] != NULL && arr[1] == NULL)
		ft_print_sort(data);
	else if (arr[0] != NULL && arr[1] != NULL)
		ft_adding_to_struct(data, arr);
	data->envp_f = 1;
}
