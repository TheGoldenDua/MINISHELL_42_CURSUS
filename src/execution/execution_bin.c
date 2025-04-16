/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:30 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:31 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	run_bin(t_cmd *cmd)
{
	char	**envp;

	envp = generate_env_arr();
	if (envp == NULL)
		malloc_error(NULL, NULL, NULL, cmd);
	if (cmd->ac > 0)
	{
		execve(cmd->binary_path, cmd->args, envp);
		perror("execve");
	}
	free_array(envp);
	exit_with_status(cmd, EXIT_SUCCESS);
}

void	execb_child(t_cmd *cmd)
{
	if (cmd->infd != STDIN_FILENO)
	{
		if (dup2(cmd->infd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit_with_status(cmd, EXIT_FAILURE);
		}
		close(cmd->infd);
	}
	if (cmd->outfd != STDOUT_FILENO)
	{
		if (dup2(cmd->outfd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit_with_status(cmd, EXIT_FAILURE);
		}
		close(cmd->outfd);
	}
	if (cmd->pipe_read != -1)
		close(cmd->pipe_read);
	run_bin(cmd);
}

void	handle_sig_quit(int sig)
{
	int		*pids;
	size_t	i;

	(void)sig;
	pids = g_minish.pids.data;
	i = 0;
	while (i < g_minish.pids.count)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
}

void	fork_error(t_cmd *cmd)
{
	perror("fork");
	exit_with_status(cmd, EXIT_FAILURE);
}

int	exec_b(t_cmd *cmd, int wait_ch)
{
	int	pid;

	if (cmd->ac > 0 && add_or_update_env("_", cmd->args[cmd->ac - 1]) == NULL)
		malloc_error(NULL, NULL, NULL, cmd);
	pid = fork();
	if (pid == -1)
		fork_error(cmd);
	if (pid == 0)
		execb_child(cmd);
	if (add_to_arr(&(g_minish.pids), &pid) == NULL)
		malloc_error(NULL, NULL, NULL, cmd);
	if (cmd->infd != STDIN_FILENO)
		close(cmd->infd);
	if (cmd->outfd != STDOUT_FILENO)
		close(cmd->outfd);
	free_cmd(cmd);
	if (signal(SIGQUIT, handle_sig_quit) == SIG_ERR)
	{
		display_error(NULL, "Can't set signal.");
		exit_with_status(NULL, EXIT_FAILURE);
	}
	if (wait_ch == FALSE)
		return (0);
	return (wait_childs());
}
