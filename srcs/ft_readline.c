/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 21:37:24 by merlich           #+#    #+#             */
/*   Updated: 2022/04/13 22:24:21 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// SUBJECT:
// The readline() function can cause memory leaks. You don’t have to fix them. But
// that doesn’t mean your own code, yes the code you wrote, can have memory
// leaks.

// NO LEAKS

char	*ft_readline(const char *prompt, t_info *data)
{
	char	*str;

	if (data->free_me.str)
		free(data->free_me.str);
	data->free_me.str = readline(prompt);
	if (data->free_me.str)
		add_history(str);
	return (data->free_me.str);
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
