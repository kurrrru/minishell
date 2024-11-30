/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:01:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 22:14:07 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static bool	containing_wildcard(const char *pattern);
static int	realloc_expanded_if_needed(t_wildcard *wild, t_config *config);
static char	**no_match(char ***expanded, const char *pattern,
				t_config *config);
static int	wildcard_match(t_wildcard *wild, const char *pattern,
				t_config *config);

char	**expand_wildcard(const char *pattern, t_config *config)
{
	t_wildcard	wild;

	wild.capacity = 2;
	wild.expanded = ft_calloc(wild.capacity, sizeof(char *));
	if (!wild.expanded)
	{
		perror("malloc");
		config->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	if (!containing_wildcard(pattern))
		return (no_match(&wild.expanded, pattern, config));
	wild.files = get_files_in_directory();
	if (!wild.files)
	{
		config->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	if (wildcard_match(&wild, pattern, config) != EXIT_SUCCESS)
		return (NULL);
	if (wild.count == 0)
		return (no_match(&wild.expanded, pattern, config));
	sort_strings(wild.expanded);
	return (wild.expanded);
}

static bool	containing_wildcard(const char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*' || pattern[i] == '?')
			return (true);
		i++;
	}
	return (false);
}

static int	realloc_expanded_if_needed(t_wildcard *wild, t_config *config)
{
	if (wild->count + 1 >= wild->capacity)
	{
		wild->capacity *= 2;
		wild->expanded = ft_realloc_char(wild->expanded, sizeof(char *)
				* (wild->capacity / 2), sizeof(char *) * wild->capacity);
		if (!wild->expanded)
		{
			perror("ft_realloc");
			config->exit_status = EXIT_FAILURE;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static char	**no_match(char ***expanded, const char *pattern,
				t_config *config)
{
	(*expanded)[0] = ft_strdup(pattern);
	if (!(*expanded)[0])
	{
		perror("malloc");
		free(*expanded);
		config->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	(*expanded)[1] = NULL;
	return (*expanded);
}

static int	wildcard_match(t_wildcard *wild, const char *pattern,
				t_config *config)
{
	size_t	i;

	i = -1;
	wild->count = 0;
	while (wild->files[++i])
	{
		if (is_match(wild->files[i], pattern))
		{
			if (realloc_expanded_if_needed(wild, config) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			wild->expanded[wild->count++] = ft_strdup(wild->files[i]);
			if (!wild->expanded[wild->count - 1])
			{
				config->exit_status = EXIT_FAILURE;
				return (perror("malloc"), free_2d(wild->expanded),
					EXIT_FAILURE);
			}
		}
		free(wild->files[i]);
	}
	free(wild->files);
	wild->expanded[wild->count] = NULL;
	return (EXIT_SUCCESS);
}

// int main(int argc, char **argv)
// {
// 	char *pattern = argc > 1 ? argv[1] : "*";
// 	char **files = expand_wildcard(pattern);
// 	int i = 0;

// 	while (files[i])
// 	{
// 		ft_putendl_fd(files[i], STDOUT_FILENO);
// 		free(files[i]);
// 		i++;
// 	}
// 	free(files);
// 	return 0;
// }
