#include "../../include/exec.h"

void	bi_env(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->envp_num)
	{
		if (config->envp[i].key && config->envp[i].value)
		{
			ft_putstr_fd(config->envp[i].key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(config->envp[i].value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
	config->exit_status = EXIT_SUCCESS;
}
