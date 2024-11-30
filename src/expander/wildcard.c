/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:01:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 17:49:14 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	**expand_wildcard(const char *pattern, t_config *config)
{
	char		**files;
	char		**expanded;
	size_t		count;
	size_t		capacity;
	size_t		i;

	files = get_files_in_directory();
	if (!files)
	{
		perror("get_files_in_directory");
		config->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	count = 0;
	capacity = 2;
	expanded = ft_calloc(capacity, sizeof(char *));
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
				expanded = ft_realloc_char(expanded, sizeof(char *)
						* (capacity / 2), sizeof(char *) * capacity);
				if (!expanded)
				{
					perror("ft_realloc");
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
