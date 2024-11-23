/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:35:57 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/03/14 12:35:57 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	ret;

	ret = 0;
	while ((*s1 != '\0' || *s2 != '\0') && n > 0)
	{
		ret = (unsigned char)*s1++ - (unsigned char)*s2++;
		if (ret != 0)
			return (ret);
		n--;
	}
	return (0);
}
