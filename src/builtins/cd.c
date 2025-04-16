/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:16:03 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:47:55 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	update_env_vars(char *old_pwd, t_cmd *cmd)
{
	char	*cwd;

	add_or_update_env("OLDPWD", old_pwd);
	free(old_pwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		exit_with_status(cmd, EXIT_FAILURE);
	}
	if (add_or_update_env("PWD", cwd) == NULL)
		malloc_error(cwd, NULL, NULL, cmd);
	free(cwd);
	return (0);
}

int	ft_cd(t_cmd cmd)
{
	int	ret_value;

	if (cmd.ac > 2)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		return (1);
	}
	if (cmd.ac == 1)
		ret_value = go_to_home(&cmd);
	else if (ft_strcmp(cmd.args[1], "-") == 0)
		ret_value = return_to_oldpwd(&cmd);
	else
		ret_value = go_to_path(cmd.args[1], &cmd);
	return (ret_value);
}
