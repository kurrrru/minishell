/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:23:25 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 23:30:46 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**make_envp(t_config *config)
{
	char	**envp;
	int		i;

	envp = (char **)malloc(sizeof(char *) * (config->envp_num + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (i < config->envp_num)
	{
		char	*key_value;
		key_value = ft_strjoin(config->envp[i].key, "=");
		if (key_value == NULL)
		{
			free_2d(envp);
			return (NULL);
		}
		envp[i] = ft_strjoin(key_value, config->envp[i].value);
		free(key_value);
		if (envp[i] == NULL)
		{
			free_2d(envp);
			return (NULL);
		}
		i++;
	}
	envp[i] = NULL;
	return (envp);
}


static void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char *get_path(char *command)
{
	char	*path_part;
	char	*path;
	char	*path_env;
	char	**path_list;
	int		i;

	path = NULL;
	if (strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		write(2, "command not found\n", 18);
		exit(127);
	}
	path_env = getenv("PATH");
	if (path_env)
		path_env = ft_strdup(path_env);
	else
		path_env = getcwd(NULL, 0);
	path_list = ft_split(path_env, ':');
	if (!path_list)
	{
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (path_list[i])
	{
		path_part = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(path_part, command);
		free(path_part);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free_split(path_list);
	if (!path)
	{
		write(STDERR_FILENO, command, strlen(command));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit(127);
	}
	free(path_env);
	return (path);
}

static void	redirect_handler(t_node *node, int *in_fd, int *out_fd)
{
	int heredoc_fd[2];
	heredoc_fd[0] = -1;
	heredoc_fd[1] = -1;
	for (int i = 0; i < node->redirect_num; i++)
	{
		if (node->redirect[i].type == HEREDOC)
		{
			if (heredoc_fd[0] != -1)
			{
				if (heredoc_fd[0] != 0)
					close(heredoc_fd[0]);
				if (heredoc_fd[1] != 1)
					close(heredoc_fd[1]);
			}
			if (pipe(heredoc_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			while (1)
			{
				char *line = readline("> ");
				if (!line)
				{
					write(2, "bash: warning: here-document delimited by end-of-file (wanted `", 61);
					write(2, node->redirect[i].file, strlen(node->redirect[i].file));
					write(2, "')\n", 3);
					break ;
				}
				if (strcmp(line, node->redirect[i].file) == 0)
				{
					free(line);
					break ;
				}
				write(heredoc_fd[1], line, strlen(line));
				write(heredoc_fd[1], "\n", 1);
				free(line);
			}
		}
	}
	if (heredoc_fd[0] != -1)
	{
		if (*in_fd != 0)
			close(*in_fd);
		*in_fd = heredoc_fd[0];
		if (heredoc_fd[1] != 1)
			close(heredoc_fd[1]);
	}
	for (int i = 0; i < node->redirect_num; i++)
	{
		if (node->redirect[i].type == IN)
		{
			if (*in_fd != 0)
				close(*in_fd);
			*in_fd = open(node->redirect[i].file, O_RDONLY);
			if (*in_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
		}
		else if (node->redirect[i].type == OUT)
		{
			if (*out_fd != 1)
				close(*out_fd);
			*out_fd = open(node->redirect[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (*out_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
		}
		else if (node->redirect[i].type == APPEND)
		{
			if (*out_fd != 1)
				close(*out_fd);
			*out_fd = open(node->redirect[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (*out_fd == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
		}
	}
}

int	run_node(t_node *node, int in_fd, int out_fd, t_config *config)
{
	t_exec	exec;

	if (!node)
	{
		ft_putendl_fd("node is NULL", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (node->type == NODE_LOGICAL_AND)
	{
		redirect_handler(node, &in_fd, &out_fd);
		config->exit_status = run_tree(node->left, in_fd, out_fd, config);
		if (config->exit_status == 0)
			return (run_tree(node->right, in_fd, out_fd, config));
		return (config->exit_status);
	}
	else if (node->type == NODE_LOGICAL_OR)
	{
		redirect_handler(node, &in_fd, &out_fd);
		config->exit_status = run_tree(node->left, in_fd, out_fd, config);
		if (config->exit_status != 0)
			config->exit_status = run_tree(node->right, in_fd, out_fd, config);
		return (config->exit_status);
	}
	else if (node->type == NODE_PIPE)
	{
		int	pipe_fd[2];
		int status;

		redirect_handler(node, &in_fd, &out_fd);
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (!node->left)
		{
			ft_putendl_fd("left is NULL", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		if (!node->right)
		{
			write(2, "right is NULL\n", 14);
			exit(EXIT_FAILURE);
		}
		int pid1, pid2;
		if (node->left->type == NODE_COMMAND)
		{
			pid1 = fork();
			if (pid1 == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid1 == 0)
			{
				close(pipe_fd[0]);
				if (out_fd != 1)
					close(out_fd);
				run_node(node->left, in_fd, pipe_fd[1], config);
			}
			else
			{
				close(pipe_fd[1]);
				if (node->right->type == NODE_COMMAND)
				{
					pid2 = fork();
					if (pid2 == -1)
					{
						perror("fork");
						exit(EXIT_FAILURE);
					}
					if (pid2 == 0)
					{
						if (in_fd != 0)
							close(in_fd);
						run_node(node->right, pipe_fd[0], out_fd, config);
					}
					else
					{
						if (in_fd != 0)
							close(in_fd);
						close(pipe_fd[0]);
						waitpid(pid1, &status, 0);
						waitpid(pid2, &status, 0);
						status = WEXITSTATUS(status);
					}
				}
				else
				{
					if (in_fd != 0)
						close(in_fd);
					int status2;
					status = run_node(node->right, pipe_fd[0], out_fd, config);
					waitpid(pid1, &status2, 0);
					close(pipe_fd[0]);
				}
			}
		}
		else
		{
			if (node->right->type == NODE_COMMAND)
			{
				pid2 = fork();
				if (pid2 == -1)
				{
					perror("fork");
					exit(EXIT_FAILURE);
				}
				if (pid2 == 0)
				{
					close(pipe_fd[1]);
					if (in_fd != 0)
						close(in_fd);
					run_node(node->right, pipe_fd[0], out_fd, config);
				}
				else
				{
					close(pipe_fd[0]);
					if (out_fd != 1)
						close(out_fd);
					status = run_node(node->left, in_fd, pipe_fd[1], config);
					close(pipe_fd[1]);
					waitpid(pid2, &status, 0);
					status = WEXITSTATUS(status);
				}
			}
			else
			{
				status = run_node(node->left, in_fd, pipe_fd[1], config);
				close(pipe_fd[1]);
				status = run_node(node->right, pipe_fd[0], out_fd, config);
				close(pipe_fd[0]);
			}
		}
		return (status);
	}
	exec.in_fd = in_fd;
	exec.out_fd = out_fd;
	redirect_handler(node, &exec.in_fd, &exec.out_fd);
	if (exec.in_fd != 0)
	{
		dup2(exec.in_fd, 0);
		close(exec.in_fd);
	}
	if (exec.out_fd != 1)
	{
		dup2(exec.out_fd, 1);
		close(exec.out_fd);
	}
	exec.command = get_path(node->command);
	exec.argv = ft_calloc(node->arg_num + 2, sizeof(char *));
	exec.argv[0] = exec.command;
	for (int i = 0; i < node->arg_num; i++)
		exec.argv[i + 1] = node->argv[i];
	exec.argv[node->arg_num + 1] = NULL;
	exec.envp = NULL;
	if (config->envp_num > 0)
	{
		exec.envp = make_envp(config);
		if (!exec.envp)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	execve(exec.command, exec.argv, exec.envp);
	perror("execve");
	exit(EXIT_FAILURE);
}