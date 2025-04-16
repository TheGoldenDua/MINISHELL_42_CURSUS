/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:12:49 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:12:51 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	node_add(t_tree_node **root, t_tree_node *new_child)
{
	t_tree_node	*node;

	if (!(*root))
	{
		*root = new_child;
		new_child->list_count++;
		return ;
	}
	(*root)->list_count++;
	node = *root;
	while (node->next)
		node = node->next;
	node->next = new_child;
}

t_tree_node	*create_node(int type)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_tree_node));
	new_node->type = type;
	new_node->data = NULL;
	return (new_node);
}

void	insert_child(t_tree_node *parent, t_tree_node *child)
{
	t_tree_node	*current_child;

	if (!parent || !child)
		return ;
	parent->childs_count++;
	if (!parent->children)
	{
		parent->children = child;
		return ;
	}
	current_child = parent->children;
	while (current_child->next)
		current_child = current_child->next;
	current_child->next = child;
}
