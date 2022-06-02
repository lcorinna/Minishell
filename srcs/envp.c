/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 12:52:50 by lcorinna          #+#    #+#             */
/*   Updated: 2022/06/02 18:41:31 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_array_envp(t_info *data)
{
	t_llist	*tmp;
	int		i;

	i = 0;
	tmp = data->envp_list;
	ft_cleaning_array(data->envp);
	while (tmp && ++i != -1)
		tmp = tmp->next;
	data->envp = malloc(sizeof(char *) * (i + 1));
	if (!data->envp)
		ft_error_exit(data, 2);
	tmp = data->envp_list;
	i = 0;
	while (tmp)
	{
		data->envp[i] = ft_strjoin_three(tmp->key, "=", tmp->value);
		if (!data->envp[i])
			ft_error_exit(data, 2);
		tmp = tmp->next;
		i++;
	}
	data->envp[i] = NULL;
	data->envp_f = 0;
	return (0);
}

int	ft_envp2(char *envp, char **key, char **value, int j)
{
	int	m;

	m = -1;
	while (envp[j + 1] != '=')
		j++;
	*key = malloc(sizeof(char) * (j + 2));
	if (!*key)
		return (1);
	while (envp[(++m)+1] != '=')
		(*key)[m] = envp[m];
	(*key)[m] = envp[m];
	(*key)[++m] = '\0';
	j++;
	m = j;
	while (envp[j])
		j++;
	*value = malloc(sizeof(char) * (j - m));
	if (!*value)
		return (ft_cleaning_str(*key));
	j = -1;
	while (envp[++m])
		(*value)[++j] = envp[m];
	(*value)[++j] = '\0';
	return (0);
}

void	ft_envp(t_info *data)
{
	t_llist	*new;
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 0;
	key = NULL;
	value = NULL;
	while (data->envp[i])
	{	
		j = 0;
		if (ft_envp2(data->envp[i], &key, &value, j))
			ft_error_exit(data, 1);
		new = ft_llstnew(key, value);
		if (!new)
			ft_error_exit(data, 1);
		ft_llstadd_back(&data->envp_list, new);
		i++;
	}
	ft_check_shlvl(data);
}

void	ft_transfer(int argc, char **argv, char **envp, t_info *data)
{	
	(void)argv;
	argc = 0;
	if (!envp)
		return ;
	while (envp[argc])
		argc++;
	data->envp = malloc(sizeof(char *) * (argc + 1));
	if (!data->envp)
		ft_perror_exit_child("", 12);
	argc = 0;
	while (envp[argc])
	{
		data->envp[argc] = ft_strdup(envp[argc]);
		if (!data->envp[argc])
		{
			perror("");
			exit(ft_cleaning_array(data->envp));
		}
		argc++;
	}
	data->envp[argc] = NULL;
	ft_envp(data);
}
