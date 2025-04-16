/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:45 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:46 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	string_randomize(char *str, int rand_fd)
{
	unsigned char	c;
	size_t			len;

	len = ft_strlen(str);
	if (read(rand_fd, str, len) == -1)
	{
		perror("read");
		exit_with_status(NULL, EXIT_FAILURE);
	}
	while (str && *str)
	{
		c = *str;
		c = (c % 10) + '0';
		*str = c;
		str++;
	}
	return (1);
}

int	interrupt_here_doc_handle(int stdin_dup)
{
	g_minish.collecting_here_doc = FALSE;
	if (dup2(stdin_dup, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit_with_status(NULL, EXIT_FAILURE);
	}
	close(stdin_dup);
	return (1);
}
