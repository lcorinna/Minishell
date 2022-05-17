/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:27:38 by merlich           #+#    #+#             */
/*   Updated: 2022/05/17 19:47:38 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **cmd_argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = ft_strncmp(cmd_argv[1], "-n", 3);
	if (cmd_argv)
	{
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
	}
}

int	main(int argc, char **argv)
{
	ft_echo(argv);
	return (0);
}
