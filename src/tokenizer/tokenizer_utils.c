/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:07 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 05:00:19 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_tree_node	*tree_node_find_by_type(t_tree_node *root, t_node_type type)
{
	t_tree_node	*tmp;

	tmp = root;
	if (!tmp)
		return (NULL);
	tmp = root->children;
	while (tmp && tmp->type != type)
		tmp = tmp->next;
	return (tmp);
}

t_tree_node	*new_node_link(t_tree_node **root, int type, int as_child)
{
	t_tree_node	*node;

	node = create_node(type);
	if (node == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
	if (as_child)
		insert_child(*root, node);
	else
		node_add(root, node);
	return (node);
}

int	logic_op_link(t_tree_node **root, t_tokenizer *tokenizer,
		t_token *token, int as_child)
{
	new_node_link(root, token->type, as_child);
	*token = get_next_token(tokenizer, TRUE);
	if (token_is_cmd(*token))
		return (1);
	return (0);
}

t_tree_node	*argv_node_link(t_tree_node *curr_cmd, t_tokenizer *tokenizer)
{
	if (string_node_ad(curr_cmd, tokenizer) == NULL)
		return (error_syntax(SYN_QUOTE));
	return (curr_cmd);
}
