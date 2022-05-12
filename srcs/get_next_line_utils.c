/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:17:38 by merlich           #+#    #+#             */
/*   Updated: 2022/05/12 22:34:46 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_chr(const char *s, int c)
{
	size_t	i;
	char	*res;

	i = 0;
	res = "";
	while (i < ft_strlen(s))
	{
		if ((unsigned char) s[i] == (unsigned char) c)
		{
			res = (char *)s + i + 1;
			return (res);
		}
		i++;
	}
	return (res);
}

void	ft_str_dup(const char *str, char *ptr)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
}
