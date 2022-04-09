/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:15:13 by merlich           #+#    #+#             */
/*   Updated: 2021/10/16 22:12:04 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				res;
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	res = 0;
	i = 0;
	p1 = (unsigned char *) s1;
	p2 = (unsigned char *) s2;
	while (i < n)
	{
		if (p1[i] != p2[i])
		{
			res = p1[i] - p2[i];
			break ;
		}
		i++;
	}
	return (res);
}
