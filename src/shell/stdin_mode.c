/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:24 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:25 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*read_entire_stdin(void)
{
	char	buff[BUFFER_SIZE];
	char	*res;
	char	*tmp;
	int		bytes;

	res = NULL;
	bytes = read(STDIN_FILENO, buff, BUFFER_SIZE - 1);
	while (bytes > 0)
	{
		buff[bytes] = 0;
		tmp = ft_strjoin(res, buff);
		if (tmp == NULL)
			malloc_error(res, NULL, NULL, NULL);
		free(res);
		res = tmp;
		bytes = read(STDIN_FILENO, buff, BUFFER_SIZE - 1);
	}
	return (res);
}

void	stdin_executor(void)
{
	g_minish.buffer = read_entire_stdin();
	if (line_parse(g_minish.buffer, &g_minish.tree_root))
		g_minish.exit_status = execute_root(g_minish.tree_root);
	else
	{
		g_minish.exit_status = 2;
		if (g_minish.interrupt == TRUE)
		{
			g_minish.interrupt = FALSE;
			close_here_docs();
			g_minish.exit_status = 130;
		}
	}
	exit_with_status(NULL, g_minish.exit_status);
}
