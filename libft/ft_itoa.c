/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:51:08 by merlich           #+#    #+#             */
/*   Updated: 2021/10/26 17:05:57 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_int_len(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i = 2;
	else
		i = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_putnbr(int n, char *ptr)
{
	if (n < 0)
	{
		n = -n;
		*ptr = '-';
		ptr = ptr + 1;
	}
	if (n / 10 != 0)
	{
		ptr = ft_putnbr(n / 10, ptr);
	}
	*ptr = n % 10 + '0';
	*(ptr + 1) = '\0';
	return (ptr + 1);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*int_min;
	char	*str;

	len = ft_int_len(n);
	int_min = "-2147483648";
	str = malloc(len + 1);
	if (NULL == str)
		return (NULL);
	else
	{
		if (n == -2147483648)
		{
			while (len > 0)
			{
				str[len - 1] = int_min[len - 1];
				len--;
			}
		}
		else
			ft_putnbr(n, str);
		return (str);
	}
}
