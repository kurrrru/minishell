/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:03:52 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/28 10:51:11 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"

static void		swap_env(t_env *env1, t_env *env2);
static void		sort_env(t_env *envp, int envp_num);
static t_env	*get_sorted_env(t_config *config);

void	export_no_argv(t_config *config)
{
	int		j;
	t_env	*sorted_env;

	sorted_env = get_sorted_env(config);
	if (!sorted_env)
		return ;
	j = -1;
	while (++j < config->envp_num)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(sorted_env[j].key, STDOUT_FILENO);
		if (!sorted_env[j].value)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			continue ;
		}
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(sorted_env[j].value, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	free(sorted_env);
	config->exit_status = EXIT_SUCCESS;
	return ;
}

static void	swap_env(t_env *env1, t_env *env2)
{
	t_env	tmp;

	tmp = *env1;
	*env1 = *env2;
	*env2 = tmp;
}

static void	sort_env(t_env *envp, int envp_num)
{
	int		i;
	int		j;

	i = 0;
	while (i < envp_num)
	{
		j = i + 1;
		while (j < envp_num)
		{
			if (ft_strcmp(envp[i].key, envp[j].key) > 0)
				swap_env(&envp[i], &envp[j]);
			j++;
		}
		i++;
	}
}

static t_env	*get_sorted_env(t_config *config)
{
	t_env	*sorted_env;
	int		i;

	sorted_env = ft_calloc(config->envp_num, sizeof(t_env));
	if (!sorted_env)
	{
		perror("malloc");
		config->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	i = -1;
	while (++i < config->envp_num)
	{
		sorted_env[i].key = config->envp[i].key;
		sorted_env[i].value = config->envp[i].value;
	}
	sort_env(sorted_env, config->envp_num);
	return (sorted_env);
}
