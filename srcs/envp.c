/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 12:52:50 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/16 14:23:08 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_malloc(int size)
{
	char	*str;

	str = malloc(sizeof(char) * size);
	if (!str)
		exit(1); //переделать
	return (str);
}

void	ft_envp2(char *envp, char *key, char *value)
{
	int	j;
	int	m;

	j = 0;
	m = -1;
	while (envp[j] != '=')
		j++;
	key = ft_malloc((j + 2));
	while (envp[(++m)] != '=')
		key[m] = envp[m];
	key[m] = envp[m];
	key[++m] = '\0';
	// printf("key - %s \n", key); //del ДЕБАГЕР
	m = j;
	while (envp[j])
		j++;
	value = ft_malloc((j - m));
	j = -1;
	while (envp[++m])
		value[++j] = envp[m];
	value[++j] = '\0';
	// printf("value - %s \n", value); //del ДЕБАГЕР
}

void	ft_envp(char **envp, t_info *data)
{
	t_llist	*new;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	key = NULL;
	value = NULL;
	data->envp = envp;
	while (envp[i])
	{
		// printf("\nenvp[%d] = %s \n", i, envp[i]); //del ДЕБАГЕР
		ft_envp2(envp[i], key, value);
		new = ft_lstnew(key, value);
		ft_lstadd_back(&data->envp_list, new);
		i++;
	}
}
