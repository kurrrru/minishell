#include "../../include/exec.h"

static void	set_bi_fd(t_node *node, t_exec *exec, t_config *config);

void	construct_bi_exec(t_exec *exec, t_node *node, t_config *config)
{
	int	i;

	set_bi_fd(node, exec, config);
	if (!node->command)
		config->exit_status = EXIT_SUCCESS;
	set_builtin_path(exec, node);
	exec->argv = ft_calloc(node->arg_num + 2, sizeof(char *));
	if (!exec->argv)
	{
		config->exit_status = EXIT_FAILURE;
		perror("malloc");
	}
	exec->argv[0] = ft_strdup(exec->command);
	i = -1;
	while (++i < node->arg_num)
		exec->argv[i + 1] = ft_strdup(node->argv[i]);
	exec->argv[node->arg_num + 1] = NULL;
	exec->envp = NULL;
	if (config->envp_num > 0)
	{
		exec->envp = make_envp(config);
		if (!exec->envp)
		{
			config->exit_status = EXIT_FAILURE;
			perror("malloc");
		}
	}
}

static void	set_bi_fd(t_node *node, t_exec *exec, t_config *config)
{
	if (redirect_handler(node, &exec->in_fd, &exec->out_fd))
		config->exit_status = EXIT_FAILURE;
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
