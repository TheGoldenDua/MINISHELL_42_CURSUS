/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:14:16 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:14:17 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_line_to_hist(char *line)
{
	t_tokenizer	tokenizer;
	t_token		token;

	tokenizer = new_tokenizer(line);
	token = get_next_token(&tokenizer, TRUE);
	if (token.type != T_EOF)
		add_history(line);
}

void	listen_for_cmd_line(void)
{
	char	*prompt;

	if (g_minish.buffer)
	{
		free(g_minish.buffer);
		g_minish.buffer = NULL;
	}
	prompt = create_prompt();
	g_minish.buffer = readline(prompt);
	free(prompt);
}

void	boot_shell(void)
{
	listen_for_cmd_line();
	while (g_minish.buffer)
	{
		add_line_to_hist(g_minish.buffer);
		g_minish.interrupt = FALSE;
		if (line_parse(g_minish.buffer, &g_minish.tree_root) != NULL)
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
		free_tree(&g_minish.tree_root);
		listen_for_cmd_line();
	}
	ft_putendl_fd("exit", STDERR_FILENO);
}
