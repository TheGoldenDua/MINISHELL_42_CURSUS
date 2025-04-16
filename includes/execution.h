/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:17:27 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:17:29 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "builtins.h"
# include "free.h"
# include "structs.h"
# include "tokenizer.h"
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

//  interpreter:
int			execute_root(t_tree_node *root);
int			process_cmd(t_tree_node *node, t_cmd *cmd);

/* piping */
int			handle_piping(t_tree_node **node, t_cmd *cmd);

//  execution:
int			exec_cmd(t_cmd *cmd, int is_pipe, int wait_child);
int			wait_childs(void);
int			exec_b(t_cmd *cmd, int wait_child);
int			exec_buil(t_cmd *cmd);
int			exec_buil_fork(t_cmd *cmd);

/* reirections */
int			handle_rdr_node(t_tree_node *cmd_node, t_cmd *cmd);

/* argv */
void		process_args(t_tree_node *cmd_node, t_cmd *cmd);

/* bin path joining */
int			get_cmd_path(t_cmd *cmd);

/* utils */
t_tree_node	*find_node_by_type(t_tree_node *root, t_node_type type);
void		get_perm_flags(int *p_flags, int *m_flags, t_node_type type);
int			is_builtin(const char *s);

/* errors */
void		display_error(char *title, char *message);

#endif