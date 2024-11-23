#include "../../include/exec.h"

void	set_builtin_path(t_exec *exec, t_node *node)
{
	if (ft_strncmp(node->command, "echo", ft_strlen("echo")) == 0)
		exec->command = "echo";
	else if (ft_strncmp(node->command, "cd", ft_strlen("cd")) == 0)
		exec->command = "cd";
	else if (ft_strncmp(node->command, "pwd", ft_strlen("pwd")) == 0)
		exec->command = "pwd";
	else if (ft_strncmp(node->command, "export", ft_strlen("export")) == 0)
		exec->command = "exoirt";
	else if (ft_strncmp(node->command, "unset", ft_strlen("unset")) == 0)
		exec->command = "unset";
	else if (ft_strncmp(node->command, "env", ft_strlen("env")) == 0)
		exec->command = "env";
	else if (ft_strncmp(node->command, "exit", ft_strlen("exit")) == 0)
		exec->command = "exit";
}

bool	is_builtin_fxn(t_node *node)
{
	if (ft_strncmp(node->command, "echo", ft_strlen("echo")) == 0)
		return (true);
	else if (ft_strncmp(node->command, "cd", ft_strlen("cd")) == 0)
		return (true);
	else if (ft_strncmp(node->command, "pwd", ft_strlen("pwd")) == 0)
		return (true);
	else if (ft_strncmp(node->command, "export", ft_strlen("export")) == 0)
		return (true);
	else if (ft_strncmp(node->command, "unset", ft_strlen("unset")) == 0)
		return (true);
	else if (ft_strncmp(node->command, "env", ft_strlen("env")) == 0)
		return (true);
	else if (ft_strncmp(node->command, "exit", ft_strlen("exit")) == 0)
		return (true);
	return (false);
}

void	exec_bi_command(t_exec exec, t_config *config)
{
	if (ft_strncmp(exec.command, "echo", ft_strlen("echo")) == 0)
		bi_echo(exec);
	else if (ft_strncmp(exec.command, "cd", ft_strlen("cd")) == 0)
		bi_cd(exec, config);
	else if (ft_strncmp(exec.command, "pwd", ft_strlen("pwd")) == 0)
		bi_pwd();
	else if (ft_strncmp(exec.command, "export", ft_strlen("export")) == 0)
		bi_export(exec, config);
	else if (ft_strncmp(exec.command, "unset", ft_strlen("unset")) == 0)
		bi_unset(exec, config);
	else if (ft_strncmp(exec.command, "env", ft_strlen("env")) == 0)
		bi_env(*config);
	else if (ft_strncmp(exec.command, "exit", ft_strlen("exit")) == 0)
		bi_exit(exec, config);
}
