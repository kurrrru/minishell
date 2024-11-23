/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:16:11 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 22:18:55 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	run_tree(t_node *root, int in_fd, int out_fd, t_config *config)
{
	int	pid;
	int	status;

	if (!root)
		return (EXIT_SUCCESS);
	if (root->type == NODE_COMMAND)
	{
		if(is_builtin_fxn(root))
			return exec_command(root, in_fd, out_fd, config);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			run_node(root, in_fd, out_fd, config);
		else
		{
			waitpid(pid, &status, 0);
			return (WEXITSTATUS(status));
		}
	}
	return (run_node(root, in_fd, out_fd, config));
}
