/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_char_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukia <rukia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:26:19 by abouguri          #+#    #+#             */
/*   Updated: 2024/11/21 22:03:31 by rukia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_p(char **p1, char **p2)
{
	char	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	ft_sort_char_arr(char **list)
{
	size_t	i;
	int		is_swapped;

	if (list == NULL || *list == NULL)
		return ;
	is_swapped = TRUE;
	while (is_swapped == TRUE)
	{
		is_swapped = FALSE;
		i = 1;
		while (list[i - 1] && list[i])
		{
			if (ft_strcmp(list[i - 1], list[i]) > 0)
			{
				ft_swap_p(&list[i - 1], &list[i]);
				is_swapped = TRUE;
			}
			i++;
		}
	}
}
