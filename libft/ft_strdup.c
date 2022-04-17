/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:46:50 by merlich           #+#    #+#             */
/*   Updated: 2022/04/17 12:15:03 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		errsv;
	char	*ptr;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (NULL == ptr)
	{
		errsv = errno;
		return (NULL);
	}
	else
	{
		while (s[i] != '\0')
		{
			ptr[i] = s[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
