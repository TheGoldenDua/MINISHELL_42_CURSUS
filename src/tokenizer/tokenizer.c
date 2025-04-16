/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:12:57 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:39:43 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	add_redirect_tree_node(t_tokenizer *tokenizer, t_tree_node *curr_cmd,
		int type)
{
	t_token		token;
	t_tree_node	*new_node;

	new_node = create_node(type);
	if (new_node == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
	insert_child(curr_cmd, new_node);
	token = get_next_token(tokenizer, TRUE);
	if (token.type == STR)
	{
		new_node = string_node_ad(new_node, tokenizer);
		if (new_node == NULL)
		{
			error_syntax(SYN_QUOTE);
			return (1);
		}
		if (type == N_HERE_DOC)
			here_doc_add(new_node);
	}
	else
	{
		error_syntax(ERR_REDIRECT);
		return (1);
	}
	return (0);
}

t_token	*cmd_fill(t_tree_node **root, t_token *token, t_tokenizer *tokenizer,
		int as_child)
{
	t_tree_node	*current_cmd;

	current_cmd = new_node_link(root, N_CMD, as_child);
	while (token_is_cmd(*token))
	{
		if (token->type == STR && argv_node_link(current_cmd,
				tokenizer) == NULL)
			return (NULL);
		else if (token_is_redirect(*token) && add_redirect_tree_node(tokenizer,
				current_cmd, token->type))
			return (NULL);
		*token = get_next_token(tokenizer, TRUE);
	}
	return (token);
}

t_tree_node	**parser_loop(t_tree_node **root, t_tokenizer *tokenizer,
		t_token *token)
{
	*root = NULL;
	g_minish.here_docs.count = 0;
	while (token->type != T_EOF)
	{
		if (token_is_cmd(*token))
		{
			token = cmd_fill(root, token, tokenizer, FALSE);
			if (token)
				continue ;
			return (NULL);
		}
		if ((*root)->list_count > 0)
		{
			if (token->type == PIPE)
			{
				if (logic_op_link(root, tokenizer, token, FALSE))
					continue ;
			}
			return (error_syntax(SYN_ERR));
		}
		else
			return (error_syntax(SYN_ERR));
		*token = get_next_token(tokenizer, TRUE);
	}
	return (here_docs_retrieve(root));
}

t_tree_node	**line_parse(char *line, t_tree_node **root)
{
	t_tokenizer	tokenizer;
	t_token		token;

	tokenizer = new_tokenizer(line);
	token = get_next_token(&tokenizer, TRUE);
	if (token.type == T_EOF)
		return (NULL);
	if (!token_is_cmd(token))
		return (error_syntax(SYN_ERR));
	return (parser_loop(root, &tokenizer, &token));
}
