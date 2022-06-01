/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:27:38 by merlich           #+#    #+#             */
/*   Updated: 2022/06/01 13:36:48 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(t_info *data, char **cmd_argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	// printf("1 - %s\n", cmd_argv[0]);
	// printf("2 - %s\n", cmd_argv[1]);
	if (cmd_argv && cmd_argv[1] != NULL)
	{
		if (cmd_argv[0] && cmd_argv[1])
			flag = ft_strncmp(cmd_argv[1], "-n", 3);
		if (!flag)
			i = 2;
		while (cmd_argv[i])
		{
			ft_putstr_fd(cmd_argv[i], 1);
			if (cmd_argv[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (flag)
			ft_putstr_fd("\n", 1);
		data->status = 0;
	}
	exit(0);
}
