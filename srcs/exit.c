/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:25:41 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/16 21:26:11 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cleaning_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
	return (1);
}

void	ft_clean_envp_list(t_info *data)
{
	while (data->free_me.envp_list)
	{
		free(data->free_me.envp_list->key);
		data->free_me.envp_list->key = NULL;
		free(data->free_me.envp_list->value);
		data->free_me.envp_list->value = NULL;
		data->free_me.envp_list = data->free_me.envp_list->next;
	}
}

void	ft_clean_struct(t_info *data)
{
	if (data->free_me.str) //строка readline
	{
		free(data->free_me.str);
		data->free_me.str = NULL;
	}
	if (data->free_me.envp) //наш envp
		ft_cleaning_array(data->free_me.envp);
	if (data->free_me.envp_list) //односвязный список
		ft_clean_envp_list(data);
}

void	ft_error_exit(t_info *data, int i)
{
	if (i == 1)
		perror("During envp creation");
	if (i == 2)
		perror("dflbnsdkfb"); //переделать
	ft_clean_struct(data);
	exit (1);
}
