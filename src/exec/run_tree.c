/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:16:11 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 21:41:26 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	run_tree(t_node *root, int in_fd, int out_fd, t_config *config)
{
	int	pid;

	if (!root)
		return (EXIT_SUCCESS);
	if (root->type == NODE_COMMAND)
	{
		set_exec_handler();
		if (is_builtin_fxn(root))
			return (exec_command(root, in_fd, out_fd, config));
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			config->is_child = 1;
			exec_command(root, in_fd, out_fd, config);
		}
		else
		{
			waitpid(pid, &config->exit_status, 0);
			config->exit_status = extract_status(config->exit_status);
			return (config->exit_status);
		}
	}
	return (run_node(root, in_fd, out_fd, config));
}
