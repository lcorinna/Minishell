/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorinna <lcorinna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:55:57 by lcorinna          #+#    #+#             */
/*   Updated: 2022/05/27 13:32:35 by lcorinna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cp_env_in_exp(t_info *data, t_llist *envp_l)
{
	t_llist	*tmp;
	t_llist	*new;
	char	*key1;
	char	*value1;

	tmp = envp_l;
	while (tmp)
	{
		key1 = ft_strdup(tmp->key);
		value1 = ft_strdup(tmp->value);
		if (key1 == NULL || value1 == NULL)
			ft_perror_exit_child("", 12);
		new = ft_llstnew(key1, value1);
		if (new == NULL)
			ft_perror_exit_child("", 12);
		ft_llstadd_back(&data->export, new);
		// printf("key - %s\n", tmp->key); //del
		tmp = tmp->next;
	}
}

char	*ft_max_key(t_llist *export)
{
	t_llist	*tmp;
	char	*res;
	char	*min;

	min = ft_strdup("                                         ");
	if (min == NULL)
		ft_perror_exit_child("", 12);
	tmp = export;
	res = min;
	while (tmp)
	{
		if (tmp->num == 0 && (ft_strncmp(res, tmp->key, ft_strlen(res)) < 0))
			res = tmp->key;
		tmp = tmp->next;
	}
	free(min);
	return (res);
}
