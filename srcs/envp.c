/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlich <merlich@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 12:52:50 by lcorinna          #+#    #+#             */
/*   Updated: 2022/04/28 22:53:29 by merlich          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_array_envp(t_info *data)
{
	t_llist	*tmp;
	int		i; //можно data->envp_f использовать счетчиком. В конце занулить!!!

	i = 0;
	tmp = data->envp_list;
	ft_cleaning_array(data->envp); //перед заходом чистим, чтобы избежать утечек
	while (!tmp)
	{
		tmp = tmp->next;
		i++;
	}
	data->envp = malloc(sizeof(char *) * (i + 1));
	if (!data->envp)
		ft_error_exit(data, 2);
	tmp = data->envp_list;
	i = 0;
	while (!tmp)
	{
		data->envp[i] = ft_strjoin(tmp->key, tmp->value);
		if (!data->envp[i])
			ft_error_exit(data, 2);
		tmp = tmp->next;
		i++;
	}
	data->envp[i] = NULL;
	data->envp_f = 0; //зануляем флаг, чтобы не заходить сюда без надобности
}

int	ft_envp2(char *envp, char **key, char **value, int j)
{
	int	m;

	m = -1;
	while (envp[j+1] != '=')  // A: 28.04.2022 убрал знак = из key
		j++;
	*key = malloc(sizeof(char) * (j + 2));
	if (!*key)
		return (1);
	while (envp[(++m)+1] != '=')  // A: 28.04.2022 убрал знак = из key
		(*key)[m] = envp[m];
	(*key)[m] = envp[m];
	(*key)[++m] = '\0';
	// printf("\nkey - %s \n", *key); //del ДЕБАГЕР
	m = j;
	while (envp[j])
		j++;
	*value = malloc(sizeof(char) * (j - m));
	if (!*value)
		return (ft_cleaning_str(*key)); //чистим key, выходим и все завершаем
	j = -1;
	while (envp[++m])
		(*value)[++j] = envp[m];
	(*value)[++j] = '\0';
	// printf("value - %s \n", *value); //del ДЕБАГЕР
	return (0);
}

void	ft_envp(t_info *data)
{
	t_llist	*new;
	char	*key;
	char	*value;
	int		i;
	int		j; //чтобы привести к норме: массивы int i[2]; и/или char *str[2];

	i = 0;
	key = NULL;
	value = NULL;
	while (data->envp[i])
	{
		j = 0;
		// printf("\nenvp[%d] = %s \n", i, envp[i]); //del ДЕБАГЕР
		if (ft_envp2(data->envp[i], &key, &value, j)) //парсинг на key и value
			ft_error_exit(data, 1);
		new = ft_lstnew(key, value); //создаю новый элемент
		if (!new)
			ft_error_exit(data, 1);
		ft_lstadd_back(&data->envp_list, new); //кладу новый элемент в конец
		i++;
	}
	// data->free_me.envp_list = data->envp_list; //пока не работает
}

void	ft_transfer(int argc, char **argv, char **envp, t_info *data)
{	
	(void)argv;
	argc = 0; //пользуюсь как счетчиком для экономии строк
	if (!envp)
		return ;
	while (envp[argc])
		argc++;
	data->envp = malloc(sizeof(char *) * (argc + 1));
	if (!data->envp)
	{
		perror("");
		exit(1); //чистить пока нечего. номер ошибки Malloc
	}
	argc = 0;
	while (envp[argc]) //копирую все в наш массив чтобы работал ft_clean_struct
	{
		data->envp[argc] = ft_strdup(envp[argc]);
		if (!data->envp[argc])
		{
			perror("");
			exit(ft_cleaning_array(data->envp)); //ошибка с чисткой и выходом
		}
		argc++;
	}
	data->envp[argc] = NULL;
	ft_envp(data); //переношу наш массив в односвязный список
}
