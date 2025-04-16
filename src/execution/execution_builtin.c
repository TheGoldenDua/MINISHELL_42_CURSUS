/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:34 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:35 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	run_blt(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(*cmd));
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(*cmd));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd(*cmd));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(*cmd));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(*cmd));
	if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(*cmd));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(*cmd));
	return (0);
}

int	exec_buil(t_cmd *cmd)
{
	int	ret_val;

	ret_val = 0;
	if (cmd->ac > 0 && add_or_update_env("_", cmd->args[cmd->ac - 1]) == NULL)
		malloc_error(NULL, NULL, NULL, cmd);
	ret_val = run_blt(cmd);
	if (cmd->infd != STDIN_FILENO)
		close(cmd->infd);
	if (cmd->outfd != STDOUT_FILENO)
		close(cmd->outfd);
	free_cmd(cmd);
	return (ret_val);
}

int	exec_buil_fork(t_cmd *cmd)
{
	int	pid;
	int	ret_val;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit_with_status(cmd, EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (cmd->pipe_read != -1)
			close(cmd->pipe_read);
		ret_val = exec_buil(cmd);
		exit_with_status(NULL, ret_val);
	}
	if (add_to_arr(&(g_minish.pids), &pid) == NULL)
		malloc_error(NULL, NULL, NULL, cmd);
	if (cmd->infd != STDIN_FILENO)
		close(cmd->infd);
	if (cmd->outfd != STDOUT_FILENO)
		close(cmd->outfd);
	free_cmd(cmd);
	return (0);
}
