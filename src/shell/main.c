/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:08 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:20:22 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_minish	g_minish;

int	main(int ac, const char **av, const char **env)
{
	(void)ac;
	(void)av;
	setup_shell(env);
	if (isatty(STDIN_FILENO))
		boot_shell();
	else
		stdin_executor();
	return (g_minish.exit_status);
}
