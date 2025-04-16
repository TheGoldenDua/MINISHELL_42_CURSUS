/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:16:24 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:16:25 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	swap_lst(t_envlist **p1, t_envlist **p2)
{
	t_envlist	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

size_t	count_exported_env_lst(void)
{
	t_envlist	*current_env;
	size_t		count;

	count = 0;
	current_env = g_minish.env_list;
	while (current_env)
	{
		count++;
		current_env = current_env->next;
	}
	return (count);
}

void	sort_env_vars(t_envlist **env_list)
{
	size_t	i;
	int		swapped;

	swapped = TRUE;
	while (swapped == TRUE)
	{
		swapped = FALSE;
		i = 1;
		while (env_list[i - 1] && env_list[i])
		{
			if (ft_strcmp(env_list[i - 1]->key, env_list[i]->key) > 0)
			{
				swap_lst(&env_list[i - 1], &env_list[i]);
				swapped = TRUE;
			}
			i++;
		}
	}
}

t_envlist	**get_sort_env_lst(void)
{
	t_envlist	*env_lst;
	t_envlist	**res;
	size_t		count;
	size_t		i;

	count = count_exported_env_lst();
	env_lst = g_minish.env_list;
	res = malloc(sizeof(t_envlist) * (count + 1));
	if (res)
	{
		i = 0;
		while (i < count)
		{
			res[i] = env_lst;
			env_lst = env_lst->next;
			i++;
		}
		res[i] = NULL;
		sort_env_vars(res);
	}
	return (res);
}
