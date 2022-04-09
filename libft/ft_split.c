/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:05:58 by merlich           #+#    #+#             */
/*   Updated: 2021/10/26 17:00:26 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_char_counter(char const *s, char c)
{	
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c) && (s[i + 1] != c))
		{
			counter++;
		}
		i++;
	}
	return (counter);
}

static size_t	ft_search(char *s, char c, size_t *index)
{
	size_t	start;

	start = 0;
	while ((start < ft_strlen(s)) && (s[start] != c))
	{
		start = start + 1;
	}
	*index = start;
	while ((*index < ft_strlen(s)) && (s[*index] == c))
	{
		*index = *index + 1;
	}
	return (start);
}

static char	**ft_action(char **tab, char *tmp, char c, size_t count)
{
	size_t	i;
	size_t	index;

	i = 0;
	index = 0;
	while ((index < ft_strlen(tmp)) && (i < count + 1))
	{
		tab[i] = ft_substr(tmp, 0, ft_search(tmp, c, &index));
		if (NULL == tab[i])
		{
			while (i > 0)
			{
				free(tab[i]);
				i--;
			}
			free(tab[0]);
			return (NULL);
		}
		tmp = tmp + index;
		index = 0;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**tab;
	char	*tmp;

	if (NULL == s)
		return (NULL);
	tmp = ft_strtrim(s, &c);
	if (NULL == tmp)
	{
		free(tmp);
		return (NULL);
	}
	count = ft_char_counter(tmp, c);
	tab = (char **)malloc(sizeof(char *) * (count + 2));
	if (NULL == tab)
	{
		free (tmp);
		return (NULL);
	}
	tab = ft_action(tab, tmp, c, count);
	free (tmp);
	return (tab);
}
