/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:42 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:38:24 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	get_here_doc_filename(char *filename)
{
	int	rand_fd;
	int	tries;

	rand_fd = open("/dev/random", O_RDONLY);
	if (rand_fd == -1)
	{
		perror("open");
		free(filename);
		exit_with_status(NULL, EXIT_FAILURE);
	}
	tries = string_randomize(filename + 25, rand_fd);
	while (tries < 100 && access(filename, F_OK) == 0)
		tries += string_randomize(filename + 25, rand_fd);
	if (access(filename, F_OK) == 0)
	{
		ft_putstr_fd(HERE_DOC_FNAME_ERROR, STDERR_FILENO);
		free(filename);
		exit_with_status(NULL, EXIT_FAILURE);
	}
	close(rand_fd);
}

void	init_here_doc(t_tree_node *node, int *fd, int *stdin_dup)
{
	char	*filename;

	filename = ft_strdup("/tmp/minishell_temp_XXXXXXXXX");
	if (filename == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
	get_here_doc_filename(filename);
	*stdin_dup = dup(0);
	if (*stdin_dup == -1)
	{
		perror("dup");
		free(filename);
		exit_with_status(NULL, EXIT_FAILURE);
	}
	*fd = open(filename, O_RDWR | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	node->here_doc_fd = open(filename, O_RDWR);
	if (*fd == -1 || node->here_doc_fd == -1)
	{
		perror("open");
		free(filename);
		exit_with_status(NULL, EXIT_FAILURE);
	}
	free(filename);
}

void	here_doc_add(t_tree_node *node)
{
	if (g_minish.here_docs.count > 15)
	{
		display_error(NULL, "maximum here-document count exceeded");
		exit_with_status(NULL, 2);
	}
	if (add_to_arr(&(g_minish.here_docs), &node) == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
}

int	get_here_doc(t_tree_node *node)
{
	int	here_doc_fd;
	int	stdin_dup;

	init_here_doc(node, &here_doc_fd, &stdin_dup);
	if (line_write_next_here_doc(node, here_doc_fd))
	{
		if (g_minish.interrupt == TRUE)
			return (interrupt_here_doc_handle(stdin_dup));
		error_syntax("expecting delim for here_doc.");
	}
	close(stdin_dup);
	g_minish.collecting_here_doc = FALSE;
	return (0);
}

t_tree_node	**here_docs_retrieve(t_tree_node **root)
{
	t_tree_node	**here_docs;
	size_t		i;

	here_docs = g_minish.here_docs.data;
	i = 0;
	while (i < g_minish.here_docs.count)
	{
		if (get_here_doc(here_docs[i]))
			return (NULL);
		i++;
	}
	g_minish.here_docs.count = 0;
	return (root);
}
