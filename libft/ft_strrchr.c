/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:17:52 by merlich           #+#    #+#             */
/*   Updated: 2021/10/20 23:18:15 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = ft_strlen(s);
	res = NULL;
	while (i >= 0)
	{
		if ((unsigned char) s[i] == (unsigned char) c)
		{
			res = (char *)s + i;
			break ;
		}
		else
			i--;
	}
	return (res);
}
