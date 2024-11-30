/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:29:48 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 19:49:53 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static void	set_fd(t_node *node, t_exec *exec);
static void	construct_exec(t_exec *exec, t_node *node, t_config *config);
static void	exec_errors(t_exec *exec, t_node *node);

int	exec_command(t_node *node, int in_fd, int out_fd, t_config *config)
{
	t_exec	exec;

	exec.in_fd = in_fd;
	exec.out_fd = out_fd;
	exec.command = NULL;
	exec.argv = NULL;
	exec.envp = NULL;
	if (!is_builtin_fxn(node))
	{
		construct_exec(&exec, node, config);
		execve(exec.command, exec.argv, exec.envp);
		exec_errors(&exec, node);
		return (EXIT_FAILURE);
	}
	else
	{
		return (exec_bi(node, &exec, config));
	}
}

static void	exec_errors(t_exec *exec, t_node *node)
{
	if (errno == EACCES)
	{
		ft_putstr_fd(node->command, STDERR_FILENO);
		if (is_directory(exec->command))
			ft_putendl_fd(": Is a directory", STDERR_FILENO);
		else
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
		exit(126);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd(node->command, STDERR_FILENO);
		ft_putendl_fd(": bad interpreter", STDERR_FILENO);
		exit(126);
	}
	perror(node->command);
	exit(126);
}

static void	construct_exec(t_exec *exec, t_node *node, t_config *config)
{
	int	i;

	set_fd(node, exec);
	if (!node->command)
		exit(EXIT_SUCCESS);
	exec->command = get_path(node->command, config);
	exec->argv = ft_calloc(node->arg_num + 2, sizeof(char *));
	if (!exec->argv)
		perror_exit("malloc", EXIT_FAILURE);
	exec->argv[0] = ft_strdup(node->command);
	if (!exec->argv[0])
		perror_exit("malloc", EXIT_FAILURE);
	i = -1;
	while (++i < node->arg_num)
		exec->argv[i + 1] = ft_strdup(node->argv[i]);
	exec->argv[node->arg_num + 1] = NULL;
	exec->envp = NULL;
	if (config->envp_num > 0)
	{
		exec->envp = make_envp(config);
		if (!exec->envp)
			perror_exit("malloc", EXIT_FAILURE);
	}
}

static void	set_fd(t_node *node, t_exec *exec)
{
	if (redirect_handler(node, &exec->in_fd, &exec->out_fd))
		exit(EXIT_FAILURE);
	if (exec->in_fd != 0)
	{
		if (dup2(exec->in_fd, 0) == -1)
			perror_exit("dup2", EXIT_FAILURE);
		close(exec->in_fd);
	}
	if (exec->out_fd != 1)
	{
		if (dup2(exec->out_fd, 1) == -1)
			perror_exit("dup2", EXIT_FAILURE);
		close(exec->out_fd);
	}
}
