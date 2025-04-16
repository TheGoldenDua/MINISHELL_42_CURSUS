/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:15:49 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:15:50 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	update_shell_lvl(void)
{
	t_envlist	*env_node;
	char		*new_val;
	int			shlvl;

	env_node = get_env_node("SHLVL");
	if (env_node)
	{
		shlvl = ft_atoi(env_node->value);
		shlvl++;
		new_val = ft_itoa(shlvl);
		if (new_val == NULL)
			malloc_error(NULL, NULL, NULL, NULL);
		env_node = add_or_update_env("SHLVL", new_val);
		free(new_val);
	}
	else
		env_node = add_or_update_env("SHLVL", "1");
	if (env_node == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
}

void	set_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
	if (add_or_update_env("PWD", pwd) == NULL)
		malloc_error(pwd, NULL, NULL, NULL);
	free(pwd);
}

void	setup_env(const char **envp)
{
	char		*key;
	char		*value;
	t_envlist	*node;
	int			i;

	g_minish.env_list = NULL;
	i = 0;
	while (envp && envp[i])
	{
		key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		if (key == NULL || value == NULL)
			malloc_error(key, value, NULL, NULL);
		node = add_env_end(&(g_minish.env_list), key, value);
		if (node == NULL)
			malloc_error(key, value, NULL, NULL);
		i++;
	}
	update_shell_lvl();
	set_pwd();
}
