/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_left_con.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 23:55:25 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/24 17:15:48 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static int	exec_pipe_left_con_right_cmd(t_node *node, t_pipe_helper ph,
				t_config *config);
static int	exec_pipe_left_con_right_con(t_node *node, t_pipe_helper ph,
				t_config *config);

int	exec_pipe_left_con(t_node *node, t_pipe_helper ph,
		t_config *config)
{
	if (node->right->type == NODE_COMMAND)
	{
		return (exec_pipe_left_con_right_cmd(node, ph, config));
	}
	else
	{
		return (exec_pipe_left_con_right_con(node, ph, config));
	}
	return (config->exit_status);
}

static int	exec_pipe_left_con_right_cmd(t_node *node, t_pipe_helper ph,
		t_config *config)
{
	set_exec_handler();
	ph.pid[1] = fork();
	if (ph.pid[1] == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (ph.pid[1] == 0)
	{
		set_exec_child_handler();
		close(ph.pipe_fd[1]);
		if (ph.in_fd != STDIN_FILENO)
			close(ph.in_fd);
		run_node(node->right, ph.pipe_fd[0], ph.out_fd, config);
	}
	else
	{
		close(ph.pipe_fd[0]);
		if (ph.out_fd != STDOUT_FILENO)
			close(ph.out_fd);
		run_node(node->left, ph.in_fd, ph.pipe_fd[1], config);
		close(ph.pipe_fd[1]);
		waitpid(ph.pid[1], &config->exit_status, 0);
		check_core_dump(config->exit_status);
		config->exit_status = extract_status(config->exit_status);
	}
	return (config->exit_status);
}

static int	exec_pipe_left_con_right_con(t_node *node, t_pipe_helper ph,
		t_config *config)
{
	run_node(node->left, ph.in_fd, ph.pipe_fd[1], config);
	close(ph.pipe_fd[1]);
	config->exit_status
		= run_node(node->right, ph.pipe_fd[0], ph.out_fd, config);
	close(ph.pipe_fd[0]);
	return (config->exit_status);
}
