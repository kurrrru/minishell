/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:16:11 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 00:07:27 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

extern sig_atomic_t	g_signal;

int	run_tree(t_node *root, int in_fd, int out_fd, t_config *config)
{
	int	pid;

	if (!root)
		return (EXIT_SUCCESS);
	if (root->type == NODE_COMMAND)
	{
		if (expand_command_node(root, config) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (is_builtin_fxn(root))
			return (exec_command(root, in_fd, out_fd, config));
		set_exec_handler();
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			set_exec_child_handler();
			config->is_child = 1;
			exec_command(root, in_fd, out_fd, config);
		}
		else
		{
			waitpid(pid, &config->exit_status, 0);
			check_core_dump(config->exit_status);
			config->exit_status = extract_status(config->exit_status);
			if (g_signal == SIGINT)
				config->exit_status = 130;
			else if (g_signal == SIGQUIT)
				config->exit_status = 131;
			return (config->exit_status);
		}
	}
	return (run_node(root, in_fd, out_fd, config));
}
