/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:16:03 by merlich           #+#    #+#             */
/*   Updated: 2021/10/20 14:26:36 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_trim_begin(char const *s1, char const *set, size_t *min)
{
	size_t	i;	
	size_t	j;

	i = 0;
	j = 0;
	while ((i <= ft_strlen(s1)) && (j < ft_strlen(set)))
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i] == set[j])
			{
				*min = *min + 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return ;
}

static void	ft_trim_end(char const *s1, char const *set, size_t *max)
{
	size_t	i;	
	size_t	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while ((i) && (j < ft_strlen(set)))
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i] == set[j])
			{
				*max = *max - 1;
				break ;
			}
			j++;
		}
		i--;
	}
	return ;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_str;
	size_t	min;
	size_t	max;

	min = 0;
	if (NULL == s1 || NULL == set)
	{
		return (NULL);
	}
	max = ft_strlen(s1) - 1;
	ft_trim_begin(s1, set, &min);
	ft_trim_end(s1, set, &max);
	if (min > max)
	{
		max = min + 1;
	}
	trim_str = ft_substr(s1, min, (max - min + 1));
	return (trim_str);
}
