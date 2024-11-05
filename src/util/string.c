/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:08:07 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/05 23:11:19 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/util.h"

char	*xstrndup(const char *s, size_t n)
{
	char	*new_s;

	new_s = (char *)xmalloc(n + 1);
	ft_strlcpy(new_s, s, n + 1);
	return (new_s);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
