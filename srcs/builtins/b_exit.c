/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:38:53 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/28 13:58:15 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_number(char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			res = 1;
		i++;
	}
	return (res);
}

void	ft_exit(t_info *data, char **arr)
{
	int		i;
	char	c;

	if (arr[1] == NULL)
		exit(data->status);
	else if (arr[2] != NULL && !ft_is_number(arr[1]))
	{
		ft_putstr_fd("exit\nminishell: exit", 2);
		ft_putstr_fd(": too many arguments\n", 2);
	}
	else if (ft_is_number(arr[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(arr[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else
	{
		i = ft_atoi(arr[1]);
		c = i;
		ft_putstr_fd("exit\n", 1);
		exit(c);
	}
}
