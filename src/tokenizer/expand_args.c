/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:53 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:54 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	**expand_argument(t_dynarr *result, char *arg)
{
	t_tokenizer	tokenizer;
	t_line		str;
	char		*s;

	tokenizer = new_tokenizer(arg);
	trim_spaces(&tokenizer);
	while (tokenizer.pos < tokenizer.count)
	{
		line_get(&tokenizer, &str, NULL);
		s = str_expand(str, REM_QUOTES);
		if (s == NULL)
			return (NULL);
		if (add_to_arr(result, &s) == NULL)
		{
			free(s);
			return (NULL);
		}
		trim_spaces(&tokenizer);
	}
	return (result->data);
}

char	**args_expansion(char **args, size_t *count)
{
	t_dynarr	result;
	size_t		i;

	result = create_dynarr(sizeof(char *));
	result.data = malloc(sizeof(char *));
	((char **)(result.data))[0] = NULL;
	result.arr_size = 1;
	i = 0;
	while (i < *count)
	{
		if (expand_argument(&result, args[i]) == NULL)
		{
			free_array(args);
			free_array(result.data);
			return (NULL);
		}
		i++;
	}
	free_array(args);
	*count = result.count;
	return (result.data);
}
