/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_manipulations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:15:52 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:15:53 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_envlist	*create_nodes(char *key, char *value)
{
	t_envlist	*new_node;

	new_node = malloc(sizeof(t_envlist));
	if (new_node == NULL)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->is_set = TRUE;
	new_node->next = NULL;
	return (new_node);
}

t_envlist	*add_env_end(t_envlist **head, char *key, char *value)
{
	t_envlist	*current;

	if (!*head)
	{
		*head = create_nodes(key, value);
		return (*head);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = create_nodes(key, value);
	return (current->next);
}

void	remove_env(t_envlist **lstenv, char *key)
{
	t_envlist	*current;
	t_envlist	*prev;

	current = *lstenv;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*lstenv = current->next;
			free_mul_p(current->key, current->value, current, NULL);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

t_envlist	*get_env_node(char *key)
{
	t_envlist	*current;

	current = g_minish.env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*get_env_value(char *key)
{
	t_envlist	*current;

	current = g_minish.env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
