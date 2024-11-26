/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:03:58 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 20:13:15 by nkawaguc         ###   ########.fr       */
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

// free_2d.c
void	free_2d(char **arr);

// free_3d.c
void	free_3d(char ***arr);

void	*xmalloc(size_t size);
void	*xrealloc(void *ptr, size_t old_size, size_t new_size);

int		extract_status(int status);

#endif
