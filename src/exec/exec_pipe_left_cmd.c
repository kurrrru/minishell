/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_left_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 23:46:11 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/24 17:42:19 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static int	exec_pipe_left_cmd_right_cmd(t_node *node, t_pipe_helper ph,
				t_config *config);
static int	exec_pipe_left_cmd_right_con(t_node *node, t_pipe_helper ph,
				t_config *config);

int	exec_pipe_left_cmd(t_node *node, t_pipe_helper ph,
		t_config *config)
{
	set_exec_handler();
	ph.pid[0] = fork();
	if (ph.pid[0] == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (ph.pid[0] == 0)
	{
		set_exec_child_handler();
		close(ph.pipe_fd[0]);
		if (ph.out_fd != STDOUT_FILENO)
			close(ph.out_fd);
		config->is_child = 1;
		run_node(node->left, ph.in_fd, ph.pipe_fd[1], config);
	}
	else
	{
		close(ph.pipe_fd[1]);
		if (ph.in_fd != STDIN_FILENO)
			close(ph.in_fd);
		if (node->right->type == NODE_COMMAND)
			config->exit_status
				= exec_pipe_left_cmd_right_cmd(node, ph, config);
		else
			config->exit_status
				= exec_pipe_left_cmd_right_con(node, ph, config);
	}
	return (config->exit_status);
}

static int	exec_pipe_left_cmd_right_cmd(t_node *node, t_pipe_helper ph,
		t_config *config)
{
	set_exec_handler();
	ph.pid[1] = fork();
	if (ph.pid[1] == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (ph.pid[1] == 0)
	{
		set_exec_child_handler();
		config->is_child = 1;
		run_node(node->right, ph.pipe_fd[0], ph.out_fd, config);
	}
	else
	{
		close(ph.pipe_fd[0]);
		waitpid(ph.pid[0], NULL, 0);
		waitpid(ph.pid[1], &config->exit_status, 0);
		check_core_dump(config->exit_status);
		config->exit_status = extract_status(config->exit_status);
	}
	return (config->exit_status);
}

static int	exec_pipe_left_cmd_right_con(t_node *node, t_pipe_helper ph,
		t_config *config)
{
	config->exit_status
		= run_node(node->right, ph.pipe_fd[0], ph.out_fd, config);
	waitpid(ph.pid[0], NULL, 0);
	check_core_dump(config->exit_status);
	close(ph.pipe_fd[0]);
	return (config->exit_status);
}
