/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:37:53 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/28 23:48:54 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_redirect *ft_realloc_redirect(t_redirect *ptr, size_t old_size, size_t new_size)
{
	t_redirect	*new_ptr;
	int			i;
	int			num;

	new_ptr = ft_realloc(ptr, old_size, new_size);
	if (!new_ptr)
	{
		num = old_size / sizeof(t_redirect);
		i = -1;
		while (++i < num)
		{
			free(ptr[i].file);
			if (ptr[i].heredoc_fd != -1)
				close(ptr[i].heredoc_fd);
		}
		free(ptr);
		return (NULL);
	}
	return (new_ptr);
}