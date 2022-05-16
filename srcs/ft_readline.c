/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:37:24 by merlich           #+#    #+#             */
/*   Updated: 2022/05/16 21:58:34 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// SUBJECT:
// The readline() function can cause memory leaks. You don’t have to fix them. 
// But that doesn’t mean your own code, yes the code you wrote, can have memory
// leaks.

// NO LEAKS

void	ft_readline(t_info *data, char *prompt, int print_exit)
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
}

// LEAKS

// char	*ft_readline(const char *prompt, t_info *data)
// {
// 	char	*str;

// 	str = readline(prompt);
// 	if (str)
// 	{
// 		data->free_me.str = str;
// 		add_history(str);
// 	}	
// 	return (str);
// }
