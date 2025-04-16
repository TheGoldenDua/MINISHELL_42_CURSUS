/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:16:21 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:16:22 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*parse_key_mode(char *arg, int *append)
{
	char	*tmp;

	*append = FALSE;
	tmp = ft_strchr(arg, '=');
	if (tmp > arg && *(tmp - 1) == '+')
	{
		*append = TRUE;
		tmp--;
	}
	return (ft_substr(arg, 0, tmp - arg));
}

void	print_env(t_cmd *cmd, t_envlist *env)
{
	ft_putstr_fd("declare -x ", cmd->outfd);
	ft_putstr_fd(env->key, cmd->outfd);
	if (env->is_set)
	{
		ft_putstr_fd("=\"", cmd->outfd);
		ft_putstr_fd(env->value, cmd->outfd);
		ft_putchar_fd('"', cmd->outfd);
	}
	write(cmd->outfd, "\n", 1);
}

int	print_exported_env(t_cmd cmd)
{
	t_envlist	**sorted_env;
	size_t		i;

	sorted_env = get_sort_env_lst();
	if (sorted_env == NULL)
		malloc_error(NULL, NULL, NULL, &cmd);
	i = 0;
	while (sorted_env && sorted_env[i])
	{
		if (ft_strcmp(sorted_env[i]->key, "_"))
			print_env(&cmd, sorted_env[i]);
		i++;
	}
	free(sorted_env);
	return (0);
}
