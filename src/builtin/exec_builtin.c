/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:26:10 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/24 18:33:57 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

void	set_builtin_path(t_exec *exec, t_node *node)
{
	if (ft_strcmp(node->command, "echo") == 0)
		exec->command = ft_strdup("echo");
	else if (ft_strcmp(node->command, "cd") == 0)
		exec->command = ft_strdup("cd");
	else if (ft_strcmp(node->command, "pwd") == 0)
		exec->command = ft_strdup("pwd");
	else if (ft_strcmp(node->command, "export") == 0)
		exec->command = ft_strdup("export");
	else if (ft_strcmp(node->command, "unset") == 0)
		exec->command = ft_strdup("unset");
	else if (ft_strcmp(node->command, "env") == 0)
		exec->command = ft_strdup("env");
	else if (ft_strcmp(node->command, "exit") == 0)
		exec->command = ft_strdup("exit");
}

bool	is_builtin_fxn(t_node *node)
{
	if (!node->command)
		return (false);
	if (ft_strcmp(node->command, "echo") == 0)
		return (true);
	else if (ft_strcmp(node->command, "cd") == 0)
		return (true);
	else if (ft_strcmp(node->command, "pwd") == 0)
		return (true);
	else if (ft_strcmp(node->command, "export") == 0)
		return (true);
	else if (ft_strcmp(node->command, "unset") == 0)
		return (true);
	else if (ft_strcmp(node->command, "env") == 0)
		return (true);
	else if (ft_strcmp(node->command, "exit") == 0)
		return (true);
	return (false);
}

void	exec_bi_command(t_exec exec, t_config *config)
{
	if (ft_strcmp(exec.command, "echo") == 0)
		bi_echo(exec, config);
	else if (ft_strcmp(exec.command, "cd") == 0)
		bi_cd(exec, config);
	else if (ft_strcmp(exec.command, "pwd") == 0)
		bi_pwd(config);
	else if (ft_strcmp(exec.command, "export") == 0)
		bi_export(exec, config);
	else if (ft_strcmp(exec.command, "unset") == 0)
		bi_unset(exec, config);
	else if (ft_strcmp(exec.command, "env") == 0)
		bi_env(config);
	else if (ft_strcmp(exec.command, "exit") == 0)
		bi_exit(exec, config);
}
