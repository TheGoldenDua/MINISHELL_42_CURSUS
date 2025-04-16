/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:15:32 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:15:33 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "structs.h"

void	display_error(char *title, char *message)
{
	ft_putstr_fd(SHELL_NAME ": ", STDERR_FILENO);
	ft_putstr_fd(title, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	print_strerr(t_line str, char *message)
{
	ft_putstr_fd(SHELL_NAME ": ", STDERR_FILENO);
	write(STDERR_FILENO, str.s, str.count);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	*error_syntax(char *message)
{
	ft_putstr_fd(SHELL_NAME ": ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	return (NULL);
}

void	malloc_error(void *p1, void *p2, char **p3, t_cmd *cmd)
{
	ft_putendl_fd(ALLOCATION_ERR, STDERR_FILENO);
	free_mul_p(p1, p2, NULL, p3);
	free_cmd(cmd);
	free_gvars();
	exit(EXIT_FAILURE);
}

void	exit_with_status(t_cmd *cmd, int exit_value)
{
	free_cmd(cmd);
	free_gvars();
	exit(exit_value);
}
