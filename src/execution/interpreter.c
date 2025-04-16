/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:15:06 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:15:07 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	process_cmd(t_tree_node *node, t_cmd *cmd)
{
	int	ret_val;

	if (cmd->outfd != STDOUT_FILENO)
	{
		close(cmd->outfd);
		cmd->outfd = STDOUT_FILENO;
	}
	ret_val = handle_rdr_node(node, cmd);
	if (ret_val)
		return (ret_val);
	cmd->type = CMD_BINARY;
	process_args(node, cmd);
	if (cmd->ac == 0)
		return (0);
	if (is_builtin(cmd->args[0]) == FALSE)
		return (get_cmd_path(cmd));
	cmd->type = CMD_BUILTIN;
	return (0);
}

t_cmd	init_cmd(void)
{
	t_cmd	cmd;

	cmd.pipe_read = -1;
	cmd.args = NULL;
	cmd.binary_path = NULL;
	cmd.infd = STDIN_FILENO;
	cmd.outfd = STDOUT_FILENO;
	return (cmd);
}

int	execute_root(t_tree_node *root)
{
	t_tree_node	*pipe_node;
	t_cmd		cmd;
	int			ret_val;

	cmd = init_cmd();
	ret_val = 0;
	while (root && g_minish.interrupt == FALSE)
	{
		pipe_node = root->next;
		if (pipe_node)
			ret_val = handle_piping(&root, &cmd);
		else
		{
			ret_val = process_cmd(root, &cmd);
			if (ret_val == 0)
				ret_val = exec_cmd(&cmd, FALSE, TRUE);
			else
				free_cmd(&cmd);
			break ;
		}
	}
	close_here_docs();
	g_minish.interrupt = FALSE;
	return (ret_val);
}
