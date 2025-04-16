/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:50 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:30:35 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_type(char a, char b)
{
	return (a == b);
}

void	get_token_type(t_tokenizer *tokenizer, t_token *token)
{
	if (!token->c || tokenizer->pos >= tokenizer->count)
		token->type = T_EOF;
	else if (is_type(token->c, '>') && is_type(tokenizer->buffer[tokenizer->pos
				+ 1], '>'))
	{
		token->type = APPEND;
		tokenizer->pos += 2;
	}
	else if (is_type(token->c, '<') && is_type(tokenizer->buffer[tokenizer->pos
				+ 1], '<'))
	{
		token->type = HERE_DOC;
		tokenizer->pos += 2;
	}
	else if (is_type(token->c, '>'))
	{
		token->type = REDIRECT_OUT;
		tokenizer->pos++;
	}
	else if (is_type(token->c, '<'))
	{
		token->type = REDIRECT_IN;
		tokenizer->pos++;
	}
}

t_token	get_next_token(t_tokenizer *tokenizer, int ignore_spaces)
{
	t_token	token;

	if (ignore_spaces)
		trim_spaces(tokenizer);
	token.c = tokenizer->buffer[tokenizer->pos];
	if (!token.c || is_type(token.c, '>') || is_type(token.c, '<'))
		get_token_type(tokenizer, &token);
	else if (is_type(token.c, '|'))
	{
		token.type = PIPE;
		tokenizer->pos++;
	}
	else
	{
		token.type = STR;
		tokenizer->pos++;
	}
	return (token);
}
