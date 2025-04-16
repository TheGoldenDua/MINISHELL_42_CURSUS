/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukia <rukia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:42:24 by abouguri          #+#    #+#             */
/*   Updated: 2024/11/21 22:00:52 by rukia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	return (ft_memmove(dest, src, n));
}

/*
int	main(int c, char**v)
{
	char	test1[50];
	char	test2[50];

	(void) c;
	(void) v;
	test1[50] = "hello world";
	test2[50] = "hello world";
	printf("%s\n", (char *)ft_memcpy(&test1[6], &test1[0], 40));
	printf("%s\n", (char *)memcpy(&test2[6], &test2[0], 40));
	return (0);
}
*/
/*
 * ST-MED
 */
