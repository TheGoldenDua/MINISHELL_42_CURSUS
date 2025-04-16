/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:16:34 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:16:35 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_cmd cmd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("get_cwd");
		exit_with_status(&cmd, EXIT_FAILURE);
	}
	ft_putendl_fd(path, cmd.outfd);
	free(path);
	return (0);
}
