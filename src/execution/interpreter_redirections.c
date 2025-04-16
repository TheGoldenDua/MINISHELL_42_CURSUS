/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:58 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:59 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	reset_prev_files(t_cmd *cmd, t_node_type rdr_type)
{
	if (cmd->infd != STDIN_FILENO && rdr_type == N_REDIRECT_IN)
	{
		close(cmd->infd);
		cmd->infd = STDIN_FILENO;
	}
	if (cmd->outfd != STDOUT_FILENO && (rdr_type == N_REDIRECT_OUT
			|| rdr_type == N_APPEND))
	{
		close(cmd->outfd);
		cmd->outfd = STDOUT_FILENO;
	}
}

int	open_rdr_file(char *filename, t_cmd *cmd, t_node_type rdr_type)
{
	int	fd;
	int	perm_flag;
	int	mode_flag;

	reset_prev_files(cmd, rdr_type);
	get_perm_flags(&perm_flag, &mode_flag, rdr_type);
	fd = open(filename, perm_flag, mode_flag);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	if (rdr_type == N_REDIRECT_IN)
		cmd->infd = fd;
	if (rdr_type == N_REDIRECT_OUT || rdr_type == N_APPEND)
		cmd->outfd = fd;
	return (0);
}

char	**expand_node_filename(t_tree_node *node, size_t *file_count)
{
	char	**expanded_fname;
	char	*expanded_str;

	expanded_fname = malloc(sizeof(char *) * 2);
	if (expanded_fname == NULL)
		return (NULL);
	expanded_fname[1] = NULL;
	expanded_str = str_expand(node->children->token_str, EXPAND_VARS);
	if (expanded_str == NULL)
		return (free_mul_p(expanded_fname, NULL, NULL, NULL));
	expanded_fname[0] = expanded_str;
	*file_count = 1;
	expanded_fname = args_expansion(expanded_fname, file_count);
	if (expanded_fname == NULL)
		return (NULL);
	if (*file_count > 1)
		return (expanded_fname);
	return (expanded_fname);
}

int	process_rdr_node(t_tree_node *node, t_cmd *cmd)
{
	char	**expanded_name;
	size_t	file_count;
	int		res;

	if (node->type == N_HERE_DOC)
	{
		if (cmd->infd != STDIN_FILENO)
			close(cmd->infd);
		cmd->infd = node->children->here_doc_fd;
		return (0);
	}
	expanded_name = expand_node_filename(node, &file_count);
	if (expanded_name == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
	if (file_count > 1)
	{
		print_strerr(node->children->token_str, "ambiguous redirect");
		free_array(expanded_name);
		return (1);
	}
	res = open_rdr_file(*expanded_name, cmd, node->type);
	free_array(expanded_name);
	return (res);
}

int	handle_rdr_node(t_tree_node *cmd_node, t_cmd *cmd)
{
	int			ret_val;
	t_tree_node	*rdr_node;

	rdr_node = find_node_by_type(cmd_node->children,
			N_REDIRECT_IN | N_REDIRECT_OUT | N_APPEND | N_HERE_DOC);
	while (rdr_node)
	{
		ret_val = process_rdr_node(rdr_node, cmd);
		if (ret_val)
			return (ret_val);
		rdr_node = find_node_by_type(rdr_node->next,
				N_REDIRECT_IN | N_REDIRECT_OUT | N_APPEND | N_HERE_DOC);
	}
	return (0);
}
