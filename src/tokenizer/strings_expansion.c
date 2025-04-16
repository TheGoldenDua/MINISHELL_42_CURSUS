/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:21 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:22 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	expand_normal_mode_2(char *res, t_line *string, size_t *i,
		t_expansion_type expansion_type)
{
	if (expansion_type & EXPAND_VARS && *(string->s) == '$')
	{
		variable_value_copy(res, string, i);
	}
	else
	{
		res[*i] = *(string->s);
		(string->count)--;
		(string->s)++;
		(*i)++;
	}
}

t_expansion_state	expand_normal_mode(char *res, t_line *string, size_t *i,
		t_expansion_type expansion_type)
{
	t_expansion_state	state;

	state = NORMAL_STATE;
	if (*(string->s) == '\'')
	{
		state = SINGLEQ_STATE;
		if (expansion_type & REM_QUOTES)
		{
			(string->count)--;
			(string->s)++;
			return (state);
		}
	}
	else if (*(string->s) == '"')
	{
		state = DOUBLEQ_STATE;
		if (expansion_type & REM_QUOTES)
		{
			(string->count)--;
			(string->s)++;
			return (state);
		}
	}
	expand_normal_mode_2(res, string, i, expansion_type);
	return (state);
}

t_expansion_state	expand_dquote_mode(char *res, t_line *string, size_t *i,
		t_expansion_type expansion_type)
{
	t_expansion_state	state;

	state = DOUBLEQ_STATE;
	if (*(string->s) == '"')
	{
		state = NORMAL_STATE;
		if (expansion_type & REM_QUOTES)
		{
			(string->count)--;
			(string->s)++;
			return (state);
		}
	}
	if (expansion_type & EXPAND_VARS && *(string->s) == '$')
	{
		variable_value_copy(res, string, i);
	}
	else
	{
		res[*i] = *(string->s);
		(string->count)--;
		(string->s)++;
		(*i)++;
	}
	return (state);
}

t_expansion_state	expand_squote_mode(char *res, t_line *string, size_t *i,
		t_expansion_type expansion_type)
{
	t_expansion_state	state;

	state = SINGLEQ_STATE;
	if (*(string->s) == '\'')
	{
		state = NORMAL_STATE;
		if (expansion_type & REM_QUOTES)
		{
			(string->count)--;
			(string->s)++;
			return (state);
		}
	}
	res[*i] = *(string->s);
	(string->count)--;
	(string->s)++;
	(*i)++;
	return (state);
}

char	*str_expansion(t_line string,
					t_expansion_type expansion_type)
{
	t_expansion_state	state;
	char				*res;
	size_t				len;
	size_t				i;

	len = expanded_string_length(string, expansion_type);
	res = malloc(len + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	state = NORMAL_STATE;
	while (string.count > 0)
	{
		if (state == NORMAL_STATE)
			state = expand_normal_mode(res, &string, &i, expansion_type);
		else if (state == DOUBLEQ_STATE)
			state = expand_dquote_mode(res, &string, &i, expansion_type);
		else if (state == SINGLEQ_STATE)
			state = expand_squote_mode(res, &string, &i, expansion_type);
	}
	res[i] = 0;
	return (res);
}
