/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:26:23 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/04/25 21:01:26 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	l;
	char	*ret;
	size_t	i;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (len + start < l)
		ret = (char *)malloc((len + 1) * sizeof(char));
	else if (start < l)
		ret = (char *)malloc((l - start + 1));
	else
		ret = (char *)malloc(1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len && i + start < l)
	{
		ret[i] = s[start + i];
		++i;
	}
	ret[i] = '\0';
	return (ret);
}
