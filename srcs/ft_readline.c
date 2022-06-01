/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:37:24 by merlich           #+#    #+#             */
/*   Updated: 2022/06/01 19:39:00 by merlich          ###   ########.fr       */
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
	if (data->str != NULL && ((data->str[0] == '\'' && data->str[1] == '\'') \
		|| (data->str[0] == '\"' && data->str[1] == '\"')))
	{
		free(data->str);
		data->str = ft_strdup(" ");
		if (data->str == NULL)
			ft_perror_exit_child("", 12);
	}
	if (!data->str && print_exit)
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
