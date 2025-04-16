/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:16:17 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:16:18 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_exit_error(char *arg, char *reason)
{
	ft_putstr_fd(SHELL_NAME ": exit: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(reason, STDERR_FILENO);
}

int	is_str_all_digits(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] >= '0' && s[i] >= '9')
			return (0);
		i++;
	}
	return (1);
}

void	handle_exit_args(t_cmd *cmd)
{
	if (cmd->ac > 2)
	{
		print_exit_error(NULL, "too many arguments");
		g_minish.exit_status = 1;
		return ;
	}
	if (ft_strlen(cmd->args[1]) > 0 && is_str_all_digits(cmd->args[1]))
		g_minish.exit_status = ft_atoi(cmd->args[1]);
	else
	{
		g_minish.exit_status = 2;
		print_exit_error(cmd->args[1], "numeric argument required");
	}
}

int	ft_exit(t_cmd cmd)
{
	if (cmd.outfd != STDOUT_FILENO)
		close(cmd.outfd);
	if (isatty(STDIN_FILENO) == 1)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd.ac > 1)
		handle_exit_args(&cmd);
	exit_with_status(&cmd, g_minish.exit_status);
	return (0);
}
