/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:03 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:04 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	token_is_cmd(t_token token)
{
	return ((token).type == STR || (token).type == REDIRECT_IN
		|| (token).type == REDIRECT_OUT || (token).type == HERE_DOC
		|| (token).type == APPEND);
}

int	token_is_redirect(t_token token)
{
	return ((token).type == REDIRECT_IN || (token).type == REDIRECT_OUT
		|| (token).type == HERE_DOC || (token).type == APPEND);
}

int	has_chars(t_line string, char *charset)
{
	size_t	i;
	size_t	j;
	size_t	charset_len;

	charset_len = ft_strlen(charset);
	i = 0;
	while (i < string.count)
	{
		j = 0;
		while (j < charset_len)
		{
			if (string.s[i] == charset[j])
				return (TRUE);
			j++;
		}
		i++;
	}
	return (FALSE);
}

int	line_write_next_here_doc(t_tree_node *node, int write)
{
	char	*line;
	char	*delim;

	g_minish.collecting_here_doc = TRUE;
	delim = str_expand(node->token_str, REM_QUOTES);
	if (delim == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, delim) == 0)
			break ;
		ft_putendl_fd(line, write);
		free(line);
		line = readline("> ");
	}
	close(write);
	free(delim);
	if (line)
	{
		free(line);
		return (0);
	}
	return (1);
}
