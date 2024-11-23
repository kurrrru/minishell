/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:39:18 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/18 00:02:13 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	exec_pipe(t_node *node, int in_fd, int out_fd, t_config *config)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	config->exit_status = redirect_handler(node, &in_fd, &out_fd);
	pid[0] = -1;
	pid[1] = -1;
	if (config->exit_status != EXIT_SUCCESS)
		return (config->exit_status);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), EXIT_FAILURE);
	if (node->left->type == NODE_COMMAND)
	{
		config->exit_status = exec_pipe_left_cmd(node, (t_pipe_helper){
				in_fd, out_fd, pipe_fd, pid}, config);
	}
	else
	{
		config->exit_status = exec_pipe_left_con(node, (t_pipe_helper){
				in_fd, out_fd, pipe_fd, pid}, config);
	}
	return (config->exit_status);
}
