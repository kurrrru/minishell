/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:11:59 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/05/03 17:33:47 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*ret;
	size_t		i;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < count * size)
		((char *)ret)[i++] = 0;
	return (ret);
}
