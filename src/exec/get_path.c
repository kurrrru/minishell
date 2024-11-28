/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 02:05:02 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/28 22:29:25 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static char	**get_path_list(t_config *config);
static char	*join_path(char *dir, char *file);
static char	*abs_or_rel_path(char *command);
static void	command_not_found(char *command);

char	*get_path(char *command, t_config *config)
{
	char	*path;
	char	**path_list;
	int		i;

	if (!command)
		exit(EXIT_SUCCESS);
	if (ft_strchr(command, '/'))
		return (abs_or_rel_path(command));
	if (ft_strcmp(command, ".") == 0 || ft_strcmp(command, "..") == 0)
		command_not_found(command);
	path_list = get_path_list(config);
	i = -1;
	while (path_list[++i])
	{
		path = join_path(path_list[i], command);
		if (access(path, F_OK) == 0)
			break ;
		else if (errno != ENOENT)
			perror_exit(command, 126);
		free(path);
		path = NULL;
	}
	if (!path)
		command_not_found(command);
	return (free_2d(path_list), path);
}

static char	**get_path_list(t_config *config)
{
	char	*path_env;
	char	**path_list;

	path_env = find_env("PATH", config);
	if (path_env)
		path_env = ft_strdup(path_env);
	else
		path_env = getcwd(NULL, 0);
	path_list = ft_split(path_env, ':');
	if (!path_list)
		perror_exit("ft_split", EXIT_FAILURE);
	free(path_env);
	return (path_list);
}

static char	*join_path(char *dir, char *file)
{
	char	*path;
	char	*path_part;

	path_part = ft_strjoin(dir, "/");
	if (!path_part)
		perror_exit("ft_strjoin", EXIT_FAILURE);
	path = ft_strjoin(path_part, file);
	free(path_part);
	if (!path)
		perror_exit("ft_strjoin", EXIT_FAILURE);
	return (path);
}

static char	*abs_or_rel_path(char *command)
{
	char	*path;
	int		i;

	path = ft_strdup(command);
	if (!path)
		perror_exit("ft_strdup", EXIT_FAILURE);
	i = ft_strlen(path) - 1;
	while (i > 0 && path[i] == '/')
	{
		path[i] = '\0';
		i--;
	}
	if (access(path, F_OK) == 0)
	{
		free(path);
		path = ft_strdup(command);
		if (!path)
			perror_exit("ft_strdup", EXIT_FAILURE);
		return (path);
	}
	else if (errno != ENOENT)
		perror_exit(command, 126);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	exit(127);
}

static void	command_not_found(char *command)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}
