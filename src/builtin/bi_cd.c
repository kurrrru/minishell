#include "../../include/exec.h"

static void	update_env(t_config *config, const char *key, const char *value);
static char	*get_env_value(t_config *config, const char *key);
static void	update_pwd(char old_cwd[1024], char *target_path, char cwd[1024],
				t_config *config);

void	bi_cd(t_exec exec, t_config *config)
{
	char	cwd[PATH_MAX];
	char	old_cwd[PATH_MAX];
	char	*target_path;

	if (!exec.argv[1])
	{
		target_path = get_env_value(config, "HOME");
		if (!target_path)
			perror_exit("cd: HOME not set", EXIT_FAILURE);
	}
	else if (ft_strncmp(exec.argv[1], "-", 1) == 0)
	{
		target_path = get_env_value(config, "OLDPWD");
		if (!target_path)
			perror_exit("cd: OLDPWD not set", EXIT_FAILURE);
	}
	else
		target_path = exec.argv[1];
	update_pwd(old_cwd, target_path, cwd, config);
}

static void	update_pwd(char old_cwd[PATH_MAX], char *target_path, char cwd[PATH_MAX],
		t_config *config)
{
	if (!getcwd(old_cwd, PATH_MAX))
		perror_exit("cd: getcwd", EXIT_FAILURE);
	if (chdir(target_path) != 0)
		perror_exit("cd: chdir failed", EXIT_FAILURE);
	if (!getcwd(cwd, PATH_MAX))
		perror_exit("cd: getcwd", EXIT_FAILURE);
	update_env(config, "OLDPWD", old_cwd);
	update_env(config, "PWD", cwd);
}

static void	update_env(t_config *config, const char *key, const char *value)
{
	int		i;
	size_t	old_size;
	size_t	new_size;

	i = -1;
	while (++i < config->envp_num)
	{
		if (ft_strncmp(config->envp[i].key, key, ft_strlen(key)) == 0)
		{
			free(config->envp[i].value);
			config->envp[i].value = ft_strdup(value);
			return ;
		}
	}
	if (config->envp_num >= config->envp_capacity)
	{
		old_size = config->envp_capacity * sizeof(t_env);
		config->envp_capacity *= 2;
		new_size = config->envp_capacity * sizeof(t_env);
		config->envp = ft_realloc(config->envp, old_size, new_size);
	}
	config->envp[config->envp_num].key = ft_strdup(key);
	config->envp[config->envp_num].value = ft_strdup(value);
	config->envp_num++;
}

static char	*get_env_value(t_config *config, const char *key)
{
	int	i;

	i = 0;
	while (i < config->envp_num)
	{
		if (ft_strncmp(config->envp[i].key, key, ft_strlen(key)) == 0)
			return (config->envp[i].value);
		i++;
	}
	return (NULL);
}
