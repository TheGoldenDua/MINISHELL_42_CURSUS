/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:16:39 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:16:40 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	process_unset_key(char *key)
{
	if (ft_strlen(key))
	{
		if (key_valid(key))
		{
			key_not_valid("unset", key);
			return (1);
		}
		else
			remove_env(&g_minish.env_list, key);
	}
	return (0);
}

int	ft_unset(t_cmd cmd)
{
	int		ret_value;
	size_t	i;

	ret_value = 0;
	i = 1;
	while (cmd.args[i])
	{
		ret_value |= process_unset_key(cmd.args[i]);
		i++;
	}
	return (ret_value);
}
