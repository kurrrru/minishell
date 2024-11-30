/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:26:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 16:47:50 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static bool	is_valid_env_name(char *name);
static void	print_invalid_identifier(char *arg, t_config *config);
static int	update_key_value(char *arg, char *equal_sign, t_config *config);

void	bi_export(t_exec exec, t_config *config)
{
	int		i;
	char	*arg;
	char	*equal_sign;

	i = 1;
	if (!exec.argv[i])
	{
		config->exit_status = EXIT_SUCCESS;
		return (export_no_argv(config));
	}
	while (exec.argv[i])
	{
		arg = exec.argv[i++];
		equal_sign = ft_strchr(arg, '=');
		if (!equal_sign)
		{
			if (is_valid_env_name(arg))
				add_or_update_env(config, arg, NULL);
			else
				print_invalid_identifier(arg, config);
		}
		else if (update_key_value(arg, equal_sign, config) == 1)
			return ;
	}
	config->exit_status = EXIT_SUCCESS;
}

static int	update_key_value(char *arg, char *equal_sign, t_config *config)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal_sign - arg);
	if (!key)
	{
		ft_putstr_fd("substr failed", STDERR_FILENO);
		config->exit_status = EXIT_FAILURE;
		return (1);
	}
	value = ft_strdup(equal_sign + 1);
	if (!value)
	{
		free(key);
		ft_putstr_fd("strdup failed", STDERR_FILENO);
		config->exit_status = EXIT_FAILURE;
		return (1);
	}
	if (is_valid_env_name(key))
		add_or_update_env(config, key, value);
	else
		print_invalid_identifier(arg, config);
	free(key);
	free(value);
	return (0);
}

static void	print_invalid_identifier(char *arg, t_config *config)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
	config->exit_status = EXIT_INVALID_INPUT;
}

static bool	is_valid_env_name(char *name)
{
	int	i;

	i = 1;
	if (!name || !(ft_isalpha(name[0]) || name[0] == '_'))
		return (false);
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}
