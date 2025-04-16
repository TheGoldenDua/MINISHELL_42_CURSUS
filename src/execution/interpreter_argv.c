/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:40 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:41 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

size_t	count_args(t_tree_node *cmd_node)
{
	size_t	ac;

	ac = 0;
	cmd_node = find_node_by_type(cmd_node->children, N_STR);
	while (cmd_node)
	{
		ac++;
		cmd_node = find_node_by_type(cmd_node->next, N_STR);
	}
	return (ac);
}

void	populate_args(t_tree_node *cmd_node, t_cmd *cmd)
{
	t_tree_node	*current_tree_node;
	size_t		i;

	current_tree_node = find_node_by_type(cmd_node->children, N_STR);
	i = 0;
	while (current_tree_node)
	{
		cmd->args[i] = str_expand(current_tree_node->token_str, EXPAND_VARS);
		i++;
		current_tree_node = find_node_by_type(current_tree_node->next, N_STR);
	}
	cmd->args = args_expansion(cmd->args, &cmd->ac);
	if (cmd->args == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
}

void	process_args(t_tree_node *cmd_node, t_cmd *cmd)
{
	cmd->binary_path = NULL;
	cmd->ac = count_args(cmd_node);
	cmd->args = malloc(sizeof(char *) * (cmd->ac + 1));
	if (cmd->args == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
	cmd->args[cmd->ac] = NULL;
	populate_args(cmd_node, cmd);
}
