/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:47:08 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/12/01 22:32:56 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static void	malloc_error(t_config *config);
static int	update_value(t_config *config, const char *value, int i);
static void	update_value_when_key_exists(t_config *config, const char *value,
				int i);

void	add_or_update_env(t_config *config, const char *key,
		const char *value)
{
	int	i;

	i = -1;
	while (++i < config->envp_num)
	{
		if (ft_strcmp(config->envp[i].key, key) == 0)
			return (update_value_when_key_exists(config, value, i));
	}
	if (config->envp_num >= config->envp_capacity - 1)
	{
		config->envp_capacity *= 2;
		config->envp = ft_realloc_env(config->envp,
				sizeof(t_env) * config->envp_capacity / 2,
				sizeof(t_env) * config->envp_capacity);
		if (!config->envp)
			return (malloc_error(config));
	}
	config->envp[config->envp_num].key = ft_strdup(key);
	if (!config->envp[config->envp_num].key)
		return (malloc_error(config));
	if (update_value(config, value, config->envp_num) != EXIT_SUCCESS)
		return (free(config->envp[config->envp_num].key));
	config->envp_num++;
}

static void	update_value_when_key_exists(t_config *config, const char *value,
		int i)
{
	if (!value)
		return ;
	free(config->envp[i].value);
	update_value(config, value, i);
}

static void	malloc_error(t_config *config)
{
	perror("malloc");
	config->exit_status = EXIT_FAILURE;
}

static int	update_value(t_config *config, const char *value, int i)
{
	if (value)
	{
		config->envp[i].value = ft_strdup(value);
		if (!config->envp[i].value)
			return (malloc_error(config), EXIT_FAILURE);
	}
	else
		config->envp[i].value = NULL;
	return (EXIT_SUCCESS);
}
