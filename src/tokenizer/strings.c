/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:16 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:17 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	line_get_whitespace(t_tokenizer *tokenizer, t_line *s,
		char *special_char_set)
{
	while (tokenizer->pos < tokenizer->count)
	{
		if (ft_isspace(tokenizer->buffer[tokenizer->pos])
			|| tokenizer->buffer[tokenizer->pos] == DOUBLEQ
			|| tokenizer->buffer[tokenizer->pos] == SINGLEQ
			|| ft_strchr(special_char_set, tokenizer->buffer[tokenizer->pos]))
			break ;
		s->count++;
		tokenizer->pos++;
	}
	return (TRUE);
}

int	line_get_delim(t_tokenizer *tokenizer, t_line *s, const char delim)
{
	int	num_of_delim;

	num_of_delim = 0;
	while (tokenizer->pos < tokenizer->count && num_of_delim < 2)
	{
		if (tokenizer->buffer[tokenizer->pos] == delim)
			num_of_delim++;
		s->count++;
		tokenizer->pos++;
	}
	if (num_of_delim == 2)
		return (TRUE);
	return (FALSE);
}

int	line_get(t_tokenizer *tokenizer, t_line *s, char *special_char_set)
{
	int	is_closed;

	s->count = 0;
	s->s = tokenizer->buffer + tokenizer->pos;
	if (*(s->s) == DOUBLEQ)
		is_closed = line_get_delim(tokenizer, s, DOUBLEQ);
	else if (*(s->s) == SINGLEQ)
		is_closed = line_get_delim(tokenizer, s, SINGLEQ);
	else
		is_closed = line_get_whitespace(tokenizer, s, special_char_set);
	while (is_closed == TRUE && s->s[s->count] && !ft_isspace(s->s[s->count])
		&& !ft_strchr(special_char_set, s->s[s->count]))
	{
		if (s->s[s->count] == DOUBLEQ)
			is_closed = line_get_delim(tokenizer, s, DOUBLEQ);
		else if (s->s[s->count] == SINGLEQ)
			is_closed = line_get_delim(tokenizer, s, SINGLEQ);
		else
			is_closed = line_get_whitespace(tokenizer, s, special_char_set);
	}
	return (is_closed);
}

t_tree_node	*string_node_ad(t_tree_node *root, t_tokenizer *tokenizer)
{
	t_tree_node	*node;

	tokenizer->pos--;
	node = create_node(N_STR);
	if (node == NULL)
		malloc_error(NULL, NULL, NULL, NULL);
	if (line_get(tokenizer, &(node->token_str), "<>|") == FALSE)
	{
		free(node);
		return (NULL);
	}
	insert_child(root, node);
	return (node);
}
