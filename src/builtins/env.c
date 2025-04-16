/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:16:13 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:16:14 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_cmd cmd)
{
	t_envlist	*head;

	head = g_minish.env_list;
	while (head)
	{
		if (head->is_set)
		{
			ft_putstr_fd(head->key, cmd.outfd);
			write(cmd.outfd, "=", 1);
			ft_putendl_fd(head->value, cmd.outfd);
		}
		head = head->next;
	}
	return (0);
}
