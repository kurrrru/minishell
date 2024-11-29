/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:40:04 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/28 23:49:05 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config.h"

t_env	*ft_realloc_env(t_env *ptr, size_t old_size, size_t new_size)
{
	t_env	*new_ptr;
	int		i;
	int		num;

	new_ptr = ft_realloc(ptr, old_size, new_size);
	if (!new_ptr)
	{
		num = old_size / sizeof(t_env);
		i = -1;
		while (++i < num)
		{
			free(ptr[i].key);
			free(ptr[i].value);
		}
		free(ptr);
		return (NULL);
	}
	return (new_ptr);
}
