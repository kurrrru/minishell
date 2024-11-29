/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:26:25 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 00:04:21 by nkawaguc         ###   ########.fr       */
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

	config->exit_status = EXIT_SUCCESS;
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
}

static void	update_pwd(char old_cwd[PATH_MAX], char *target_path,
		char cwd[PATH_MAX], t_config *config)
{
	getcwd(old_cwd, PATH_MAX);
	if (chdir(target_path) == -1)
	{
		perror(target_path);
		config->exit_status = EXIT_FAILURE;
		return ;
	}
	if (!old_cwd)
	{
		ft_putendl_fd("cd: getcwd", STDERR_FILENO);
		config->exit_status = EXIT_FAILURE;
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd("cd: getcwd", STDERR_FILENO);
		config->exit_status = EXIT_FAILURE;
	}
	update_env(config, "OLDPWD", old_cwd);
	update_env(config, "PWD", cwd);
}

static void	update_env(t_config *config, const char *key, const char *value)
{
	int		i;

	i = -1;
	while (++i < config->envp_num)
	{
		if (ft_strcmp(config->envp[i].key, key) == 0)
		{
			free(config->envp[i].value);
			config->envp[i].value = ft_strdup(value);
			if (!config->envp[i].value)
			{
				perror("malloc");
				config->exit_status = EXIT_FAILURE;
				return ;
			}
			return ;
		}
	}
	if (config->envp_num >= config->envp_capacity)
	{
		config->envp_capacity *= 2;
		config->envp = ft_realloc_env(config->envp,
				sizeof(t_env) * (config->envp_capacity / 2),
				sizeof(t_env) * config->envp_capacity);
		if (!config->envp)
		{
			perror("malloc");
			config->exit_status = EXIT_FAILURE;
			return ;
		}
	}
	config->envp[config->envp_num].key = ft_strdup(key);
	config->envp[config->envp_num].value = ft_strdup(value);
	if (!config->envp[config->envp_num].key
		|| !config->envp[config->envp_num].value)
	{
		perror("malloc");
		config->exit_status = EXIT_FAILURE;
		free(config->envp[config->envp_num].key);
		free(config->envp[config->envp_num].value);
		return ;
	}
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
