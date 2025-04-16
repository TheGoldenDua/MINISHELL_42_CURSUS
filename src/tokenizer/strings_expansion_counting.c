/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_expansion_counting.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:38 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:39 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	count_normal_mode_2(t_line string, size_t *i, size_t *len,
		t_expansion_type expansion_type)
{
	if (expansion_type & EXPAND_VARS && string.s[*i] == '$')
	{
		var_len_count(string, i, len);
	}
	else
	{
		(*i)++;
		(*len)++;
	}
}

t_expansion_state	count_normal_mode(t_line string, size_t *i, size_t *len,
		t_expansion_type expansion_type)
{
	t_expansion_state	state;

	state = NORMAL_STATE;
	if (string.s[*i] == '\'')
	{
		state = SINGLEQ_STATE;
		if (expansion_type & REM_QUOTES)
		{
			(*i)++;
			return (state);
		}
	}
	else if (string.s[*i] == '"')
	{
		state = DOUBLEQ_STATE;
		if (expansion_type & REM_QUOTES)
		{
			(*i)++;
			return (state);
		}
	}
	count_normal_mode_2(string, i, len, expansion_type);
	return (state);
}

t_expansion_state	count_dquote_mode(t_line string, size_t *i, size_t *len,
		t_expansion_type expansion_type)
{
	t_expansion_state	state;

	state = DOUBLEQ_STATE;
	if (string.s[*i] == '"')
	{
		state = NORMAL_STATE;
		if (expansion_type & REM_QUOTES)
		{
			(*i)++;
			return (state);
		}
	}
	if (expansion_type & EXPAND_VARS && string.s[*i] == '$')
	{
		var_len_count(string, i, len);
	}
	else
	{
		(*i)++;
		(*len)++;
	}
	return (state);
}

t_expansion_state	count_squote_mode(t_line string, size_t *i, size_t *len,
		t_expansion_type expansion_type)
{
	t_expansion_state	state;

	state = SINGLEQ_STATE;
	if (string.s[*i] == '\'')
	{
		state = NORMAL_STATE;
		if (expansion_type & REM_QUOTES)
		{
			(*i)++;
			return (state);
		}
	}
	(*i)++;
	(*len)++;
	return (state);
}

size_t	expanded_string_length(t_line string, t_expansion_type expansion_type)
{
	t_expansion_state	state;
	size_t				len;
	size_t				i;

	len = 0;
	i = 0;
	state = NORMAL_STATE;
	while (i < string.count)
	{
		if (state == NORMAL_STATE)
			state = count_normal_mode(string, &i, &len, expansion_type);
		else if (state == DOUBLEQ_STATE)
			state = count_dquote_mode(string, &i, &len, expansion_type);
		else if (state == SINGLEQ_STATE)
			state = count_squote_mode(string, &i, &len, expansion_type);
	}
	return (len);
}
