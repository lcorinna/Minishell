/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:51:46 by merlich           #+#    #+#             */
/*   Updated: 2021/10/20 21:30:47 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	const char	*src1;
	char		*dest1;

	i = 0;
	src1 = (const char *) src;
	dest1 = (char *) dst;
	if (!(NULL == src && NULL == dst))
	{
		while (i < n)
		{
			dest1[i] = src1[i];
			i++;
		}
	}
	return (dst);
}
