/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 12:52:50 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/16 21:22:54 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_array_envp(t_info *data)
{
	t_llist	*tmp;
	int		i;

	i = 0;
	tmp = data->envp_list;
	while (!tmp)
	{
		tmp = tmp->next;
		i++;
	}
	data->envp = malloc(sizeof(char *) * (i + 1));
	if (!data->envp)
		ft_error_exit(data, 1);
	tmp = data->envp_list;
	i = 0;
	while (!tmp)
	{
		data->envp[i] = ft_strjoin(tmp->key, tmp->value);
		if (!data->envp[i])
			ft_error_exit(data, 1); //проверить
		tmp = tmp->next;
		i++;
	}
	data->envp[i] = NULL;
}

int	ft_envp2(char *envp, char *key, char *value, int j)
{
	int	m;

	m = -1;
	while (envp[j] != '=')
		j++;
	key = malloc(sizeof(char) * (j + 2));
	if (!key)
		return (1);
	while (envp[(++m)] != '=')
		key[m] = envp[m];
	key[m] = envp[m];
	key[++m] = '\0';
	// printf("key - %s \n", key); //del ДЕБАГЕР
	m = j;
	while (envp[j])
		j++;
	value = malloc(sizeof(char) * (j - m));
	if (!value)
		return (1);
	j = -1;
	while (envp[++m])
		value[++j] = envp[m];
	value[++j] = '\0';
	// printf("value - %s \n", value); //del ДЕБАГЕР
	return (0);
}

void	ft_envp(char **envp, t_info *data)
{
	t_llist	*new;
	char	*key;
	char	*value;
	int		i;
	int		j; //чтобы привести к норме: массивы int i[2] и/или char *str[2];

	i = 0;
	key = NULL;
	value = NULL;
	while (envp[i])
	{
		j = 0;
		// printf("\nenvp[%d] = %s \n", i, envp[i]); //del ДЕБАГЕР
		if (ft_envp2(envp[i], key, value, j))
		{
			if (key)
				free(key);
			ft_error_exit(data, 1);
		}
		new = ft_lstnew(key, value);
		if (!new)
			ft_error_exit(data, 1);
		ft_lstadd_back(&data->envp_list, new);
		data->free_me.envp_list = data->envp_list;
		i++;
	}
	if (data->envp_list)
		ft_array_envp(data);
}
