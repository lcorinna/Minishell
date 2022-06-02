/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:25:41 by lcorinna          #+#    #+#             */
/*   Updated: 2022/06/01 22:08:09 by lcorinna         ###   ########.fr       */
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
	return (1);
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
	return (1);
}

void	ft_clean_envp_list(t_llist *llist)
{
	t_llist	*tmp;

	tmp = llist;
	while (llist)
	{
		free(tmp->key);
		tmp->key = NULL;
		free(tmp->value);
		tmp->value = NULL;
		tmp = tmp->next;
		free(llist);
		llist = NULL;
		llist = tmp;
	}
}

void	ft_clean_struct(t_info *data)
{
	ft_cleanup(data);
	if (data->str)
	{
		free(data->str);
		data->str = NULL;
	}
	if (data->envp)
		ft_cleaning_array(data->envp);
	if (data->envp_list)
		ft_clean_envp_list(data->envp_list);
	if (data->export)
		ft_clean_envp_list(data->export);
}

void	ft_error_exit(t_info *data, int i)
{
	if (i == 1)
		perror("During envp creation");
	else if (i == 2)
		perror("Failed to create envp from the list");
	ft_clean_struct(data);
	data->status = 1;
	exit (1);
}
