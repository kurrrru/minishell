/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_get_files_in_directory.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:40:44 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 17:50:58 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static int	add_to_files(char ***files, int *count, int *capacity, char *entry);

char	**get_files_in_directory(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**files;
	int				count;
	int				capacity;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	capacity = 2;
	files = ft_calloc(capacity, sizeof(char *));
	if (!files)
		return (NULL);
	files[0] = NULL;
	count = -1;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (add_to_files(&files, &count, &capacity, entry->d_name)
			!= EXIT_SUCCESS)
			return (closedir(dir), NULL);
	}
	return (closedir(dir), files);
}

static int	add_to_files(char ***files, int *count, int *capacity, char *entry)
{
	if (*count + 1 >= *capacity)
	{
		*capacity *= 2;
		*files = ft_realloc_char(*files, sizeof(char *) * (*capacity / 2),
				sizeof(char *) * *capacity);
		if (!*files)
			return (perror("ft_realloc"), EXIT_FAILURE);
	}
	(*files)[++*count] = ft_strdup(entry);
	if (!(*files)[*count])
		return (perror("malloc"), free_2d(*files), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
