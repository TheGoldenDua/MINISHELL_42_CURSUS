/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_or_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:15:45 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:15:46 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_envlist	*allocate_env_node(char *key, char *value)
{
	char	*key_cpy;
	char	*value_cpy;

	key_cpy = ft_strdup(key);
	if (key_cpy == NULL)
		return (NULL);
	if (value)
	{
		value_cpy = ft_strdup(value);
		if (value_cpy == NULL)
			return (free_mul_p(key_cpy, NULL, NULL, NULL));
		return (add_env_end(&(g_minish.env_list), key_cpy, value_cpy));
	}
	return (add_env_end(&(g_minish.env_list), key_cpy, NULL));
}

t_envlist	*add_new_env(char *key, char *value)
{
	t_envlist	*node;

	node = allocate_env_node(key, value);
	if (!node)
		return (NULL);
	if (!value)
		node->is_set = FALSE;
	return (node);
}

t_envlist	*replace_env(t_envlist *node, char *value)
{
	char	*value_cpy;

	if (value)
	{
		value_cpy = ft_strdup(value);
		if (value_cpy == NULL)
			return (NULL);
		free_mul_p(node->value, NULL, NULL, NULL);
		node->value = value_cpy;
		node->is_set = TRUE;
	}
	return (node);
}

t_envlist	*add_or_update_env(char *key, char *value)
{
	t_envlist	*node;

	node = get_env_node(key);
	if (node)
		node = replace_env(node, value);
	else
		node = add_new_env(key, value);
	return (node);
}
