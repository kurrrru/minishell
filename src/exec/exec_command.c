/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:29:48 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/18 00:33:44 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static void	set_fd(t_node *node, t_exec *exec);
static void	exec_errors(t_exec *exec);

int	exec_command(t_node *node, int in_fd, int out_fd, t_config *config)
{
	t_exec	exec;
	int		i;

	exec.in_fd = in_fd;
	exec.out_fd = out_fd;
	set_fd(node, &exec);
	exec.command = get_path(node->command);
	exec.argv = ft_calloc(node->arg_num + 2, sizeof(char *));
	if (!exec.argv)
		perror_exit("malloc", EXIT_FAILURE);
	exec.argv[0] = exec.command;
	i = -1;
	while (++i < node->arg_num)
		exec.argv[i + 1] = node->argv[i];
	exec.argv[node->arg_num + 1] = NULL;
	exec.envp = NULL;
	if (config->envp_num > 0)
	{
		exec.envp = make_envp(config);
		if (!exec.envp)
			perror_exit("malloc", EXIT_FAILURE);
	}
	execve(exec.command, exec.argv, exec.envp);
	exec_errors(&exec);
	exit(EXIT_FAILURE);
}

static void	exec_errors(t_exec *exec)
{
	if (errno == EACCES)
	{
		ft_putstr_fd(exec->command, STDERR_FILENO);
		if (is_directory(exec->command))
			ft_putendl_fd(": Is a directory", STDERR_FILENO);
		else
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
		exit(126);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd(exec->command, STDERR_FILENO);
		ft_putendl_fd(": bad interpreter", STDERR_FILENO);
		exit(126);
	}
	perror(exec->command);
	exit(126);
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
