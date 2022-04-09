/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:37:37 by merlich           #+#    #+#             */
/*   Updated: 2021/10/16 11:14:03 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		start;
	size_t		stop;
	int			step;

	if (dst != src)
	{
		if (dst > src)
		{
			start = len - 1;
			step = -1;
			stop = -1;
		}
		if (dst < src)
		{
			start = 0;
			step = 1;
			stop = len;
		}
		while (start != stop)
		{
			((char *)(dst))[start] = ((const char *)(src))[start];
			start += step;
		}
	}
	return (dst);
}
