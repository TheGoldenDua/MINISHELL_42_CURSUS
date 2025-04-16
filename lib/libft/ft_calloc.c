/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukia <rukia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:33:37 by abouguri          #+#    #+#             */
/*   Updated: 2024/11/18 17:11:59 by rukia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*
int	main(int c, char**v)
{
	void	*p1;
	void	*p2;

	(void) c;
	(void) v;
	p1 = ft_calloc(SIZE_MAX - 2, 0);
	p2 = calloc(SIZE_MAX - 2, 0);
	printf("%p, %p\n", p1, p2);
}
*/
/*
 * ST-MED
 */
