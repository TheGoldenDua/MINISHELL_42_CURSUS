/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukia <rukia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 00:41:37 by abouguri          #+#    #+#             */
/*   Updated: 2024/11/21 22:00:30 by rukia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == ((unsigned char)c))
			return (&(((unsigned char *)s)[i]));
		i++;
	}
	return (NULL);
}

/*
#include <string.h>

void	check_segv(int i)
{
	printf("Reached here: %d\n", i);
	fflush(0);
}

int	main(int c, char**v)
{
	(void) c;
	//printf("%p\n", ft_memchr(0, 'b',10));
	check_segv(0);
	printf("%p\n", memchr(0, 'x',10000));
	check_segv(1);
}
*/
/*
 * ST-MED
 */
