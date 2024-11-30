/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_bi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:04:36 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 19:48:16 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static void	set_bi_fd(t_node *node, t_exec *exec, t_config *config);

int	construct_bi_exec(t_exec *exec, t_node *node, t_config *config)
{
	int	i;

	set_bi_fd(node, exec, config);
	if (config->exit_status != EXIT_SUCCESS)
		return (config->exit_status);
	set_builtin_path(exec, node);
	if (exec->command == NULL)
		return (perror("malloc"), EXIT_FAILURE);
	exec->argv = ft_calloc(node->arg_num + 2, sizeof(char *));
	if (!exec->argv)
		return (perror("malloc"), EXIT_FAILURE);
	exec->argv[0] = ft_strdup(exec->command);
	if (!exec->argv[0])
		return (perror("malloc"), EXIT_FAILURE);
	i = -1;
	while (++i < node->arg_num)
		exec->argv[i + 1] = ft_strdup(node->argv[i]);
	exec->envp = NULL;
	if (config->envp_num > 0)
	{
		exec->envp = make_envp(config);
		if (!exec->envp)
			return (perror("malloc"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	set_bi_fd(t_node *node, t_exec *exec, t_config *config)
{
	if (redirect_handler(node, &exec->in_fd, &exec->out_fd))
	{
		config->exit_status = EXIT_FAILURE;
		return ;
	}
	if (exec->in_fd != 0)
	{
		if (dup2(exec->in_fd, 0) == -1)
		{
			config->exit_status = EXIT_FAILURE;
			perror("dup2");
		}
		close(exec->in_fd);
	}
	if (exec->out_fd != 1)
	{
		if (dup2(exec->out_fd, 1) == -1)
		{
			config->exit_status = EXIT_FAILURE;
			perror("dup2");
		}
		close(exec->out_fd);
	}
}
