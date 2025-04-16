/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:37 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:38 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	wait_single_child(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit_with_status(NULL, EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_childs(void)
{
	int		exit_status;
	int		*pids;
	size_t	i;

	pids = g_minish.pids.data;
	exit_status = 0;
	i = 0;
	while (i < g_minish.pids.count)
	{
		exit_status = wait_single_child(pids[i]);
		i++;
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		display_error(NULL, "Can't set signal.");
		exit_with_status(NULL, EXIT_FAILURE);
	}
	g_minish.pids.count = 0;
	if (g_minish.interrupt == TRUE)
		return (130);
	return (exit_status);
}

int	exec_cmd(t_cmd *cmd, int is_pipe, int wait_ch)
{
	if (cmd->type == CMD_BINARY)
		return (exec_b(cmd, wait_ch));
	else if (cmd->type == CMD_BUILTIN)
	{
		if (is_pipe == TRUE)
			return (exec_buil_fork(cmd));
		else
			return (exec_buil(cmd));
	}
	display_error(NULL, "Unsupported command type");
	return (0);
}
