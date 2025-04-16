/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_piping.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:49 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:50 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	wait_for_last_pipe_cmd(t_cmd *cmd, int status)
{
	if (status == 0)
	{
		exec_cmd(cmd, TRUE, FALSE);
		status = wait_childs();
	}
	else
	{
		if (cmd->infd != STDIN_FILENO)
			close(cmd->infd);
		if (cmd->outfd != STDOUT_FILENO)
			close(cmd->outfd);
		free_cmd(cmd);
		wait_childs();
	}
	return (status);
}

void	execute_command_in_pipe(t_cmd *cmd, int status, int pipe_fds[2])
{
	if (status == 0)
	{
		if (cmd->outfd == STDOUT_FILENO)
			cmd->outfd = pipe_fds[1];
		else
			close(pipe_fds[1]);
		cmd->pipe_read = pipe_fds[0];
		exec_cmd(cmd, TRUE, FALSE);
		cmd->infd = pipe_fds[0];
	}
	else
	{
		close(pipe_fds[1]);
		if (cmd->infd != STDIN_FILENO)
			close(cmd->infd);
		cmd->infd = pipe_fds[0];
		free_cmd(cmd);
	}
}

void	add_cmd_to_pipe(t_cmd *cmd, int status)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror(cmd->args[0]);
		exit_with_status(cmd, EXIT_FAILURE);
	}
	execute_command_in_pipe(cmd, status, pipe_fds);
}

int	handle_piping(t_tree_node **node, t_cmd *cmd)
{
	int	status;

	cmd->infd = STDIN_FILENO;
	cmd->outfd = STDOUT_FILENO;
	while (TRUE)
	{
		status = process_cmd(*node, cmd);
		(*node) = (*node)->next;
		if (*node == NULL || (*node)->type != N_PIPE)
			break ;
		add_cmd_to_pipe(cmd, status);
		*node = (*node)->next;
	}
	return (wait_for_last_pipe_cmd(cmd, status));
}
