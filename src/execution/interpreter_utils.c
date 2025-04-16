/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:15:02 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:15:03 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_tree_node	*find_node_by_type(t_tree_node *root, t_node_type target_type)
{
	t_tree_node	*current_n;

	current_n = root;
	while (current_n && !(current_n->type & target_type))
		current_n = current_n->next;
	return (current_n);
}

void	get_perm_flags(int *perm_flags, int *mode_flags, t_node_type rdr_type)
{
	if (rdr_type == N_REDIRECT_IN)
	{
		*perm_flags = O_RDONLY;
		*mode_flags = 0;
	}
	else if (rdr_type == N_REDIRECT_OUT)
	{
		*perm_flags = O_WRONLY | O_CREAT | O_TRUNC;
		*mode_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	}
	else if (rdr_type == N_APPEND)
	{
		*perm_flags = O_WRONLY | O_APPEND | O_CREAT;
		*mode_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	}
}

int	is_builtin(const char *cmd)
{
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}
