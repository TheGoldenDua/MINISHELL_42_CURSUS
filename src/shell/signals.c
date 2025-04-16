/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:20 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:21 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_minish.interrupt = TRUE;
	g_minish.exit_status = 130;
	if (g_minish.pids.count > 0)
	{
		write(1, "\n", 1);
		return ;
	}
	if (g_minish.collecting_here_doc == TRUE)
	{
		write(1, "\n", 1);
		close(0);
		return ;
	}
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
}

void	signal_handler_setup(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		display_error(NULL, "Can't set signal.");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		display_error(NULL, "Can't set signal.");
		exit(EXIT_FAILURE);
	}
}
