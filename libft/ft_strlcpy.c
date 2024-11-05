/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/02/23 18:26:32 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/02/23 18:26:32 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src,
		size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		if (i + 1 < dstsize)
			dst[i] = src[i];
		i++;
	}
	if (i >= dstsize && dstsize > 0)
		dst[dstsize - 1] = '\0';
	else if (dstsize > 0)
		dst[i] = '\0';
	return (i);
}
