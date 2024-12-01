/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:26:25 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/12/01 20:46:01 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static char	*get_env_value(t_config *config, const char *key);
static void	update_pwd(char old_cwd[PATH_MAX], char *target_path,
				char cwd[PATH_MAX], t_config *config);
static int	cd_set_home(t_config *config, char **target_path);
static int	cd_set_oldpwd(t_config *config, char **target_path);

void	bi_cd(t_exec exec, t_config *config)
{
	char	cwd[PATH_MAX];
	char	old_cwd[PATH_MAX];
	char	*target_path;

	config->exit_status = EXIT_SUCCESS;
	if (!exec.argv[1])
	{
		if (cd_set_home(config, &target_path) != EXIT_SUCCESS)
			return ;
	}
	else if (ft_strcmp(exec.argv[1], "-") == 0)
	{
		if (cd_set_oldpwd(config, &target_path) != EXIT_SUCCESS)
			return ;
	}
	else if (exec.argv[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		config->exit_status = EXIT_FAILURE;
		return ;
	}
	else
		target_path = exec.argv[1];
	update_pwd(old_cwd, target_path, cwd, config);
}

static int	cd_set_home(t_config *config, char **target_path)
{
	*target_path = get_env_value(config, "HOME");
	if (!*target_path)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		config->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	cd_set_oldpwd(t_config *config, char **target_path)
{
	*target_path = get_env_value(config, "OLDPWD");
	if (!*target_path)
	{
		ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
		config->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
	add_or_update_env(config, "OLDPWD", old_cwd);
	add_or_update_env(config, "PWD", cwd);
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
