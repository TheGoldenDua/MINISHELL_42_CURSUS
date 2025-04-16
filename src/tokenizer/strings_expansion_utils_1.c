/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_expansion_utils_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:34 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:35 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*str_expand(t_line string, t_expansion_type expansion_type)
{
	if (has_chars(string, "'\"$") == TRUE)
		return (str_expansion(string, expansion_type));
	else
		return (ft_substr(string.s, 0, string.count));
}
