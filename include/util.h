/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:03:58 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/14 23:12:47 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "include.h"
# include "macro.h"

// ft_realloc.c
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

// ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);

void	*xmalloc(size_t size);
void	*xrealloc(void *ptr, size_t old_size, size_t new_size);

char	*xstrndup(const char *s, size_t n);

#endif
