/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:15:36 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:15:37 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_cmd(t_cmd *cmd)
{
	char	*av;

	if (!cmd)
		return ;
	av = NULL;
	if (cmd->args)
	{
		av = cmd->args[0];
		free_array(cmd->args);
	}
	if (cmd->binary_path && av != cmd->binary_path)
		free(cmd->binary_path);
	cmd->args = NULL;
	cmd->binary_path = NULL;
}

void	clear_env_list(t_envlist *list_head)
{
	t_envlist	*current;
	t_envlist	*next_node;

	current = list_head;
	while (current)
	{
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		next_node = current->next;
		free(current);
		current = next_node;
	}
}

void	free_gvars(void)
{
	free_mul_p(g_minish.buffer, g_minish.pids.data, NULL, NULL);
	g_minish.buffer = NULL;
	g_minish.pids.data = NULL;
	g_minish.pids.arr_size = 0;
	clear_env_list(g_minish.env_list);
	free_tree(&g_minish.tree_root);
	close_here_docs();
}

void	close_here_docs(void)
{
	struct stat	s;
	int			fd;

	fd = 3;
	while (fd > 2 && fstat(fd, &s) != -1)
	{
		close(fd);
		fd++;
	}
}
