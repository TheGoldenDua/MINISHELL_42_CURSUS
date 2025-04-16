/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 04:13:58 by imoulasr          #+#    #+#             */
/*   Updated: 2024/12/20 04:13:59 by imoulasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_dynarr	create_dynarr(size_t size)
{
	t_dynarr	new_array;
	int			value;

	value = 0;
	new_array.data_size = size;
	new_array.arr_size = value;
	new_array.count = value;
	new_array.data = NULL;
	return (new_array);
}

t_dynarr	*resize_array(t_dynarr *array)
{
	void	*new_data;

	if (array == NULL)
		return (NULL);
	array->arr_size += DA_DEFAULT_CAPACITY;
	new_data = malloc(array->arr_size * array->data_size);
	if (new_data == NULL)
		return (NULL);
	ft_memset(new_data, 0, array->arr_size * array->data_size);
	if (array->data && array->count > 0)
		ft_memcpy(new_data, array->data, array->data_size * array->count);
	if (array->data)
		free(array->data);
	array->data = new_data;
	return (array);
}

t_dynarr	*add_to_arr(t_dynarr *array, void *element)
{
	if (array->arr_size == 0 || array->count >= array->arr_size - 1)
		if (resize_array(array) == NULL)
			return (NULL);
	ft_memcpy(((unsigned char *)array->data) + array->count * array->data_size,
		element, array->data_size);
	array->count++;
	return (array);
}
