/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical_and.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:29:54 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/29 11:19:10 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static int	exec_logical_and(t_node *node, int in_fd,
				int out_fd, t_config *config);
static int	exec_logical_or(t_node *node, int in_fd,
				int out_fd, t_config *config);

int	exec_logical_connectors(t_node *node, int in_fd,
		int out_fd, t_config *config)
{
	if (node->type == NODE_LOGICAL_AND)
		return (exec_logical_and(node, in_fd, out_fd, config));
	else if (node->type == NODE_LOGICAL_OR)
		return (exec_logical_or(node, in_fd, out_fd, config));
	return (EXIT_FAILURE);
}

static int	exec_logical_and(t_node *node, int in_fd,
		int out_fd, t_config *config)
{
	config->exit_status = redirect_handler(node, &in_fd, &out_fd);
	if (config->exit_status != EXIT_SUCCESS)
		return (config->exit_status);
	config->exit_status = run_tree(node->left, in_fd, out_fd, config);
	if (config->exit_status == EXIT_SUCCESS)
	{
		config->last_exit_status = config->exit_status;
		config->exit_status = run_tree(node->right, in_fd, out_fd, config);
	}
	return (config->exit_status);
}

static int	exec_logical_or(t_node *node, int in_fd,
		int out_fd, t_config *config)
{
	config->exit_status = redirect_handler(node, &in_fd, &out_fd);
	if (config->exit_status != EXIT_SUCCESS)
		return (config->exit_status);
	config->exit_status = run_tree(node->left, in_fd, out_fd, config);
	if (config->exit_status != EXIT_SUCCESS)
	{
		config->last_exit_status = config->exit_status;
		config->exit_status = run_tree(node->right, in_fd, out_fd, config);
	}
	return (config->exit_status);
}
