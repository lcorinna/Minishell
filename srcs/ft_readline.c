/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:37:24 by merlich           #+#    #+#             */
/*   Updated: 2022/05/31 22:38:20 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline(t_info *data, char *prompt, int print_exit)
{
	if (data->str)
		ft_cleaning_str(data->str);
	data->str = readline(prompt);
	if (data->str)
		add_history(data->str);
	else if (!data->str && print_exit)
	{
		ft_putstr_fd("\x1b[1F", 2);
		ft_putstr_fd(SHELL, 2);
		ft_putstr_fd("exit\n", 2);
	}
	else if (!data->str && !print_exit)
	{
		ft_perror_eof(data);
	}
	return (data->str);
}
