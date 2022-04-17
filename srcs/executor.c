/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/17 20:14:37 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_creating_a_path(char **envp, int *num)
{
	int	check;

	check = 0;
	while (envp[*num] != NULL && check != 5)
		check = ft_memcmp("PATH=", envp[(*num)++], 5);
	if (check != 5)
		return (0);
	(*num)++;
	return (1);
}

void	parse_path(t_info *data, int i)
{
	if (data->envp != NULL && ft_creating_a_path(data->envp, &i))
	{
		data->path = ft_split(data->envp[i] + 5, ':');
		if (data->path == NULL)
		{
			
		}
	}
}

void	executor(t_info *data)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	parse_path(data, i);
	while (check != 0 && data->path[i] != NULL)
		check = access(data->path[i++], F_OK);
	if (check == -1)
		ft_exit_with_cleaning(data, NULL, 1); //переделать
	data->pid = fork();
	if (data->pid == 0)
		if (execve(data->path[i], data->free_me.str, data->envp) == -1)
			ft_exit_with_cleaning(data, NULL, 4); //переделать
}
