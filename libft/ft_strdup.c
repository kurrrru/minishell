/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:25:03 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/04/25 23:38:31 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*ret;
	size_t		len;

	len = ft_strlen(s1);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, len + 1);
	return (ret);
}
