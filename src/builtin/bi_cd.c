/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:26:25 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/24 19:58:24 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static void	update_env(t_config *config, const char *key, const char *value);
static char	*get_env_value(t_config *config, const char *key);
static void	update_pwd(char old_cwd[PATH_MAX], char *target_path,
				char cwd[PATH_MAX], t_config *config);

void	bi_cd(t_exec exec, t_config *config)
{
	char	cwd[PATH_MAX];
	char	old_cwd[PATH_MAX];
	char	*target_path;

	if (!exec.argv[1])
	{
		target_path = get_env_value(config, "HOME");
		if (!target_path)
		{
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
			config->exit_status = EXIT_FAILURE;
			return ;
		}
	}
	else if (ft_strcmp(exec.argv[1], "-") == 0)
	{
		target_path = get_env_value(config, "OLDPWD");
		if (!target_path)
		{
			ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
			config->exit_status = EXIT_FAILURE;
			return ;
		}
	}
	else
		target_path = exec.argv[1];
	update_pwd(old_cwd, target_path, cwd, config);
	config->exit_status = EXIT_SUCCESS;
}

static void	update_pwd(char old_cwd[PATH_MAX], char *target_path,
		char cwd[PATH_MAX], t_config *config)
{
	getcwd(old_cwd, PATH_MAX);
	if (chdir(target_path) != 0)
	{
		perror(target_path);
		config->exit_status = EXIT_INVALID_INPUT;
		return ;
	}
	if (!old_cwd)
	{
		ft_putendl_fd("cd: getcwd", STDERR_FILENO);
		config->exit_status = EXIT_INVALID_INPUT;
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd("cd: getcwd", STDERR_FILENO);
		config->exit_status = EXIT_INVALID_INPUT;
	}
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
		if (ft_strcmp(config->envp[i].key, key) == 0)
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
		if (ft_strcmp(config->envp[i].key, key) == 0)
			return (config->envp[i].value);
		i++;
	}
	return (NULL);
}
