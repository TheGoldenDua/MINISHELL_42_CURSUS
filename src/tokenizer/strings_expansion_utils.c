/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_expansion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:26 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:27 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

size_t	key_count_parse(const char *str)
{
	size_t	i;

	i = 0;
	if (!str[i] || ft_isspace(str[i]))
		return (-1);
	if (ft_isdigit(str[i]))
		return (++i);
	else if (str[i] == '$' || str[i] == '?' || str[i] == '*')
		return (++i);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		i++;
	}
	return (i);
}

int	chars_count_num(long n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	perform_var_value_copy(char *res, t_line *string, size_t *i,
		int key_count)
{
	char	key[BUFFER_SIZE];
	char	*value;

	ft_strlcpy(key, string->s, key_count + 1);
	if (ft_strcmp(key, "?") == 0)
		*i += ft_sitoa(res + *i, g_minish.exit_status);
	else
	{
		value = get_env_value(key);
		if (value)
			*i += ft_strlcpy(res + *i, value, INT32_MAX);
	}
	(string->count) -= key_count;
	(string->s) += key_count;
}

void	variable_value_copy(char *res, t_line *string, size_t *i)
{
	int	key_count;

	(string->count)--;
	(string->s)++;
	key_count = key_count_parse(string->s);
	if (key_count > 0 && key_count < BUFFER_SIZE - 1)
	{
		perform_var_value_copy(res, string, i, key_count);
	}
	else if (key_count == -1)
	{
		res[*i] = '$';
		(*i)++;
	}
}

void	var_len_count(t_line string, size_t *i, size_t *len)
{
	int		count;
	char	buff[BUFFER_SIZE];

	(*i)++;
	count = key_count_parse(string.s + *i);
	if (count > 0 && count < BUFFER_SIZE - 1)
	{
		ft_strlcpy(buff, string.s + *i, count + 1);
		if (ft_strcmp(buff, "?") == 0)
			*len += chars_count_num(g_minish.exit_status);
		else
			*len += ft_strlen(get_env_value(buff));
		*i += count;
	}
	else if (count == -1)
	{
		(*len)++;
	}
}
