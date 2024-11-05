/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:53:44 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/02/15 18:53:44 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst - src < 0)
	{
		i = 0;
		while (++i <= len)
			((char *)dst)[i - 1] = ((char *)src)[i - 1];
	}
	else if (dst - src > 0)
	{
		i = len + 1;
		while (--i > 0)
			((char *)dst)[i - 1] = ((char *)src)[i - 1];
	}
	return (dst);
}
