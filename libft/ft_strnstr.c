/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:50:30 by merlich           #+#    #+#             */
/*   Updated: 2021/10/21 17:41:58 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_compare(const char *haystack, const char *needle, \
						size_t len, size_t len_needle)
{
	size_t		i;
	size_t		j;
	size_t		start;

	i = 0;
	j = 0;
	start = 0;
	while ((i < len) && (haystack[i] != '\0') && (start + len_needle - 1 < len))
	{
		if (haystack[i] == needle[j])
		{
			j++;
			i++;
		}
		else
		{
			j = 0;
			i = start + 1;
			start++;
		}
		if (j == len_needle)
			return ((char *)(haystack + i - len_needle));
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		len_needle;
	char		*ptr;

	len_needle = ft_strlen(needle);
	ptr = NULL;
	if (len_needle == 0)
	{
		return ((char *)(haystack));
	}
	ptr = ft_compare(haystack, needle, len, len_needle);
	return (ptr);
}
