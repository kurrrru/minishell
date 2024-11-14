/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:08:07 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/14 22:49:39 by nkawaguc         ###   ########.fr       */
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