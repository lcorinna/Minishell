/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:27:13 by merlich           #+#    #+#             */
/*   Updated: 2021/10/16 17:21:19 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*res;
	unsigned char	*s1;

	i = 0;
	res = NULL;
	s1 = (unsigned char *)s;
	while (i < n)
	{
		if (s1[i] == (unsigned char) c)
		{
			res = s1 + i;
			break ;
		}
		i++;
	}
	return (res);
}
