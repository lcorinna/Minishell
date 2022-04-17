/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:25:41 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/17 20:22:53 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cleaning_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (1); //Д: использую эту единичку
}

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
	return (1); //Д: использую эту единичку
}

void	ft_clean_envp_list(t_info *data)
{
	t_llist	*tmp;

	tmp = data->envp_list;
	while (data->envp_list)
	{
		free(tmp->key);
		tmp->key = NULL;
		free(tmp->value);
		tmp->value = NULL;
		tmp = tmp->next;
		free(data->envp_list);
		data->envp_list = NULL;
		data->envp_list = tmp;
	}
}

void	ft_clean_struct(t_info *data)
{
	// if (data->free_me.str) //строка readline кажется, что не нужна??
	// {
	// 	printf("1\n"); //del
	// 	free(data->free_me.str);
	// 	data->free_me.str = NULL;
	// }
	if (data->envp) //наш envp
	{
		// printf("2\n"); //del
		ft_cleaning_array(data->envp);
	}
	if (data->envp_list) //односвязный список
	{
		// printf("3\n"); //del
		ft_clean_envp_list(data);
	}
}

void	ft_error_exit(t_info *data, int i)
{
	if (i == 1)
		perror("During envp creation");
	else if (i == 2)
		perror("Failed to create envp from the list"); //переделать
	ft_clean_struct(data);
	exit (1);
}
