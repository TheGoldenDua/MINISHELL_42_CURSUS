/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exported_env_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:15:56 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:15:57 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

char	*construct_env(char *key, char *value)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (tmp == NULL)
		return (NULL);
	while (key && *key)
	{
		tmp[i] = *key;
		key++;
		i++;
	}
	tmp[i] = '=';
	i++;
	while (value && *value)
	{
		tmp[i] = *value;
		value++;
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

size_t	exp_env_size(void)
{
	t_envlist	*lst;
	size_t		size;

	size = 0;
	lst = g_minish.env_list;
	while (lst)
	{
		if (lst->is_set == TRUE)
			size++;
		lst = lst->next;
	}
	return (size);
}

char	**generate_env_arr(void)
{
	t_envlist	*env_node;
	char		**res;
	size_t		i;

	res = malloc(sizeof(char *) * (exp_env_size() + 1));
	if (res == NULL)
		return (NULL);
	ft_memset(res, 0, sizeof(char *) * (exp_env_size() + 1));
	env_node = g_minish.env_list;
	i = 0;
	while (env_node)
	{
		if (env_node->is_set == TRUE)
		{
			res[i] = construct_env(env_node->key, env_node->value);
			if (res[i] == NULL)
				return (free_mul_p(NULL, NULL, NULL, res));
			i++;
		}
		env_node = env_node->next;
	}
	res[i] = NULL;
	return (res);
}
