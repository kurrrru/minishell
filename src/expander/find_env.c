/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:56:20 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 13:04:11 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static char	*dup_env_value(const char *value, t_config *config);

char	*find_env(const char *key, t_config *config)
{
	int		i;
	char	*value;

	if (key[0] == '?')
	{
		value = ft_itoa(config->last_exit_status);
		if (!value)
		{
			perror("malloc");
			config->exit_status = EXIT_FAILURE;
		}
		return (value);
	}
	i = -1;
	while (++i < config->envp_num)
		if (ft_strcmp(key, config->envp[i].key) == 0)
			return (dup_env_value(config->envp[i].value, config));
	value = ft_strdup("");
	if (!value)
	{
		perror("malloc");
		config->exit_status = EXIT_FAILURE;
	}
	return (value);
}

static char	*dup_env_value(const char *value, t_config *config)
{
	char	*dup_value;

	if (!value)
		dup_value = ft_strdup("");
	else
		dup_value = ft_strdup(value);
	if (!dup_value)
	{
		perror("malloc");
		config->exit_status = EXIT_FAILURE;
	}
	return (dup_value);
}
