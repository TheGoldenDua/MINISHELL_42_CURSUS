/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:05 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:06 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "shell.h"

void	init_variables(void)
{
	g_minish.exit_status = 0;
	g_minish.interrupt = FALSE;
	g_minish.collecting_here_doc = FALSE;
}

void	setup_shell(const char **envp)
{
	g_minish.pids = create_dynarr(sizeof(int));
	g_minish.here_docs = create_dynarr(sizeof(t_tree_node *));
	signal_handler_setup();
	setup_env(envp);
	init_variables();
}
