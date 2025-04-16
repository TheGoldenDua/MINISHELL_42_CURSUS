/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:11 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:12 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_tokenizer	new_tokenizer(char *line)
{
	t_tokenizer	tokenizer;

	tokenizer.buffer = line;
	tokenizer.count = ft_strlen(line);
	tokenizer.pos = 0;
	return (tokenizer);
}

void	trim_spaces(t_tokenizer *tokenizer)
{
	while (tokenizer->pos < tokenizer->count
		&& ft_isspace(tokenizer->buffer[tokenizer->pos]))
		tokenizer->pos++;
}
