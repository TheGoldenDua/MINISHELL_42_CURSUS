/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:17:19 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:17:20 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "execution.h"
# include "structs.h"
# include <signal.h>

typedef struct s_minish
{
	t_envlist	*env_list;
	t_tree_node	*tree_root;
	t_dynarr	pids;
	t_dynarr	here_docs;
	char		*buffer;
	int			exit_status;
	int			interrupt;
	int			collecting_here_doc;
}				t_minish;

extern t_minish	g_minish;

void			setup_shell(const char **envp);
void			signal_handler_setup(void);
void			boot_shell(void);
void			stdin_executor(void);
char			*create_prompt(void);

#endif