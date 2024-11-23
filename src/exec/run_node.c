/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:23:25 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/18 00:34:18 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	run_node(t_node *node, int in_fd, int out_fd, t_config *config)
{
	if (node->type == NODE_LOGICAL_AND || node->type == NODE_LOGICAL_OR)
		return (exec_logical_connectors(node, in_fd, out_fd, config));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(node, in_fd, out_fd, config));
	exec_command(node, in_fd, out_fd, config);
	exit(EXIT_FAILURE);
}
