/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/11 21:11:31 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_creating_a_path(char **envp, int *num)
{
	int	check;

	check = 1;
	while (envp[*num] != NULL && check != 0)
		check = ft_memcmp("PeATH=", envp[(*num)++], 5); //сломано нужно чинить
	printf("check %d\n", check); //del
	if (ft_memcmp("PATH=", envp[(*num) - 1], 5))
		return (0);
	(*num)++;
	return (1);
}

int	ft_parse_path(t_info *data, int i)
{
	if (data->envp != NULL && ft_creating_a_path(data->envp, &i))
	{
		printf("HERE\n"); //del
		data->path = ft_split(data->envp[i] + 5, ':');
		if (data->path == NULL)
		{
			perror("");
			return (1);
		}
	}
	return (0);
}

int	ft_how_many_cmd(t_info *data)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = data->tokens;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

// void	ft_one_cmd(t_info *data)
// {

// }

int	ft_executor(t_info *data)
{
	int	i;
	int	cmd;
	int	check;

	i = 0;
	cmd = ft_how_many_cmd(data); //считаю кол-во команд, чтобы уйти на ветвление
	if (cmd == 0)
		return (0);
	if (ft_parse_path(data, i))
		return (1);
	printf("data->envp - %s\n", data->envp[0]); //del
	// else if (cmd == 1)
	// 	ft_one_cmd(data);
	// else if (cmd > 1)
	printf("\n data.tokens %s\n", data->tokens->str_val); //del
	check = 1;
	return (0); //выход чтобы не ругался компилятор (временное решение)
	while (check != 0 && data->path[i] != NULL)
		check = access(data->path[i++], F_OK);
	if (check == -1)
		ft_exit_with_cleaning(data, NULL, 1); //переделать
	data->pid = fork();
	if (data->pid == 0)
		if (execve(data->path[i], data->free_me.str, data->envp) == -1)
			ft_exit_with_cleaning(data, NULL, 4); //переделать
}
