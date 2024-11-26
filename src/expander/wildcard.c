/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:01:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 19:23:16 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static char	**get_files_in_directory(void);
static void	sort_strings(char **strings);

char	**expand_wildcard(const char *pattern, t_config *config)
{
	const char	**files = get_files_in_directory();
	char		**expanded;
	size_t		count;
	size_t		capacity;
	size_t		i;

	if (!files)
	{
		perror("get_files_in_directory");
		config->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	count = 0;
	capacity = 2;
	expanded = malloc(sizeof(char *) * capacity);
	if (!expanded)
	{
		perror("malloc");
		config->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	expanded[0] = NULL;
	i = 0;
	while (files[i])
	{
		if (is_match(files[i], (char *)pattern))
		{
			if (count + 1 >= capacity)
			{
				capacity *= 2;
				expanded = ft_realloc(expanded, sizeof(char *)
						* (capacity / 2), sizeof(char *) * capacity);
				if (!expanded)
				{
					perror("ft_realloc");
					free_2d(expanded);
					config->exit_status = EXIT_FAILURE;
					return (NULL);
				}
			}
			expanded[count] = ft_strdup(files[i]);
			if (!expanded[count])
			{
				perror("malloc");
				free_2d(expanded);
				config->exit_status = EXIT_FAILURE;
				return (NULL);
			}
			count++;
		}
		free(files[i]);
		i++;
	}
	free(files);
	if (count > 0)
	{
		expanded[count] = NULL;
	}
	else
	{
		expanded[0] = ft_strdup(pattern);
		if (!expanded[0])
			return (free(expanded), NULL);
		expanded[1] = NULL;
	}
	sort_strings(expanded);
	return (expanded);
}

static char	**get_files_in_directory(void)
{
	const DIR		*dir = opendir(".");
	struct dirent	*entry;
	char			**files;
	size_t			count;
	size_t			capacity;

	if (!dir)
		return (NULL);
	capacity = 2;
	files = malloc(sizeof(char *) * capacity);
	if (!files)
		return (NULL);
	files[0] = NULL;
	count = -1;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		capacity *= 2;
		files = ft_realloc(files, sizeof(char *) * (capacity / 2),
				sizeof(char *) * capacity);
		files[++count] = ft_strdup(entry->d_name);
		if (!files[count])
		{
			perror("malloc");
			free_2d(files);
			closedir(dir);
			return (NULL);
		}
	}
	files[++count] = NULL;
	closedir(dir);
	return (files);
}

static void	sort_strings(char **strings)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = 0;
	while (strings[len])
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(strings[i], strings[j]) > 0)
			{
				tmp = strings[i];
				strings[i] = strings[j];
				strings[j] = tmp;
			}
			j++;
		}
		i++;
	}
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
