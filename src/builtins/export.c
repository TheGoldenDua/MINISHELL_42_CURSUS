/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:16:30 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:16:31 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_envlist	*update_env_value(t_envlist *node, char *value)
{
	char	*tmp;

	if (node == NULL)
		return (free_mul_p(value, NULL, NULL, NULL));
	node->is_set = TRUE;
	tmp = ft_strjoin(node->value, value);
	free_mul_p(node->value, NULL, NULL, NULL);
	if (tmp == NULL)
		return (free_mul_p(value, NULL, NULL, NULL));
	node->value = tmp;
	return (node);
}

t_envlist	*add_env(char *key, char *arg, int append)
{
	char		*value;
	t_envlist	*node;

	value = ft_strdup(ft_strchr(arg, '=') + 1);
	if (value == NULL)
		return (NULL);
	if (append == TRUE)
		node = update_env_value(add_or_update_env(key, NULL), value);
	else
	{
		node = add_or_update_env(key, value);
		free(value);
	}
	return (node);
}

void	add_to_env_lst(t_cmd *cmd, char *arg, char *key, int append)
{
	t_envlist	*node;

	if (ft_strchr(arg, '='))
		node = add_env(key, arg, append);
	else
		node = add_or_update_env(key, NULL);
	if (node == NULL)
		malloc_error(key, NULL, NULL, cmd);
}

int	process_export_env(t_cmd *cmd, size_t i)
{
	int		ret_value;
	int		append;
	char	*key;

	key = parse_key_mode(cmd->args[i], &append);
	if (key == NULL)
		malloc_error(NULL, NULL, NULL, cmd);
	ret_value = 0;
	if (ft_strlen(key) && key_valid(key) == 0)
		add_to_env_lst(cmd, cmd->args[i], key, append);
	else
		ret_value = key_not_valid("export", key);
	free(key);
	return (ret_value);
}

int	ft_export(t_cmd cmd)
{
	int		tmp;
	int		ret_value;
	size_t	i;

	if (cmd.ac == 1)
		return (print_exported_env(cmd));
	ret_value = 0;
	i = 1;
	while (i < cmd.ac)
	{
		tmp = process_export_env(&cmd, i);
		if (ret_value == 0)
			ret_value = tmp;
		i++;
	}
	return (ret_value);
}
