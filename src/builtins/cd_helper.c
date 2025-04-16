/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:41:59 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:48:02 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	change_directory(char *path, char *old_pwd, t_cmd *cmd)
{
	if (chdir(path) == -1)
	{
		free(old_pwd);
		perror(SHELL_NAME ": cd");
		return (1);
	}
	return (update_env_vars(old_pwd, cmd));
}

int	go_to_path(char *path, t_cmd *cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		exit_with_status(cmd, EXIT_FAILURE);
	}
	if (access(path, X_OK) != 0)
	{
		free(cwd);
		perror(SHELL_NAME ": cd");
		return (1);
	}
	return (change_directory(path, cwd, cmd));
}

int	go_to_home(t_cmd *cmd)
{
	char	*home;

	home = get_env_value("HOME");
	if (!home)
	{
		write(STDERR_FILENO, "cd: HOME not set\n", 17);
		return (1);
	}
	return (go_to_path(home, cmd));
}

int	return_to_oldpwd(t_cmd *cmd)
{
	char	*oldpwd;
	int		ret_value;

	oldpwd = get_env_value("OLDPWD");
	if (!oldpwd)
	{
		write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
		return (1);
	}
	ret_value = go_to_path(oldpwd, cmd);
	if (ret_value == 0)
		ft_pwd(*cmd);
	return (ret_value);
}
