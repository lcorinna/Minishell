/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:29:33 by merlich           #+#    #+#             */
/*   Updated: 2021/10/16 22:59:44 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int					res;
	size_t				i;
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *) s1;
	p2 = (const unsigned char *) s2;
	res = 0;
	i = 0;
	while ((i < n) && ((p1[i] != '\0') || (p2[i] != '\0')))
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
