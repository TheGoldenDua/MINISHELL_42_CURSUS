/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:15:40 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:15:41 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "structs.h"

void	*free_mul_p(void *p1, void *p2, void *p3, char **p4)
{
	if (p1)
		free(p1);
	if (p2)
		free(p2);
	if (p3)
		free(p3);
	if (p4)
		free_array(p4);
	return (NULL);
}

void	*free_array(char **array)
{
	char	**tmp;

	tmp = array;
	while (array && *array)
	{
		free(*array);
		array++;
	}
	if (array)
		free(tmp);
	return (NULL);
}

void	free_childs(t_tree_node *parent)
{
	t_tree_node	*tmp;
	t_tree_node	*node;

	node = parent->children;
	while (node)
	{
		if (node->children)
			free_childs(node);
		tmp = node->next;
		free(node);
		node = tmp;
	}
}

void	free_tree(t_tree_node **root)
{
	t_tree_node	*tmp;
	t_tree_node	*node;

	node = *root;
	while (node)
	{
		if (node->children)
			free_childs(node);
		tmp = node->next;
		free(node);
		node = tmp;
	}
	*root = NULL;
}
