#include "../../include/exec.h"

static void	del_env(int k, t_config *config);

void	bi_unset(t_exec exec, t_config *config)
{
	int	i;
	int	j;

	i = 1;
	if (!exec.argv[i])
		return ;
	while (exec.argv[i])
	{
		j = 0;
		while (j < config->envp_num)
		{
			if (ft_strncmp(exec.argv[i], config->envp[j].key,
					ft_strlen(exec.argv[i]) + 1) == 0)
			{
				del_env(j, config);
				break ;
			}
			j++;
		}
		i++;
	}
}

static void	del_env(int k, t_config *config)
{
	free(config->envp[k].key);
	free(config->envp[k].value);
	while (k < config->envp_num - 1)
	{
		config->envp[k] = config->envp[k + 1];
		k++;
	}
	config->envp_num--;
	config->envp[config->envp_num].key = NULL;
	config->envp[config->envp_num].value = NULL;
}
