/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:26:57 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/28 23:29:55 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/util.h"

char	**ft_realloc_char(char **ptr, size_t old_size, size_t new_size)
{
	char	**new_ptr;

	new_ptr = ft_realloc(ptr, old_size, new_size);
	if (!new_ptr)
	{
		free_2d(ptr);
		return (NULL);
	}
	return (new_ptr);
}
