/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:45:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/04/25 21:06:43 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	sep[256];
	int	i;
	int	len;

	if (!s1 || !set)
		return (NULL);
	ft_bzero(sep, 256 * sizeof(int));
	i = -1;
	while (set[++i] != '\0')
		sep[(int)set[i]] = 1;
	while (*s1 && sep[(int)*s1])
		s1++;
	len = ft_strlen(s1);
	while (sep[(int)s1[--len]])
		;
	return (ft_substr(s1, 0, len + 1));
}
